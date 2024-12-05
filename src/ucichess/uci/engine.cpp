
#include "engine.hpp"
#include "../error/error.hpp"
#include <cstring>
#include <fcntl.h>

#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

namespace ucichess {
  // split_s is the core machinery. It split s at splitPoint, and returns a vector.
  std::vector<std::string> split_s(const std::string& s, char delimeter) {
    std::vector<std::string> elements;
    std::stringstream string_stream(s);
    std::string item;
    while(std::getline(string_stream, item, delimeter)) {
      elements.push_back(item);
    }
    return elements;
  }
  // printf("read %ld bytes: %s\n", (long)nread, s);

  ChessEngine::ChessEngine(const std::string& path)
      : m_path{path} {
    ux::File parentToChild1;
    ux::File parentToChild2;
    ux::File childToParent1;
    ux::File childToParent2;

    EC_CATCH(f::pipe(parentToChild1, parentToChild2));
    EC_CATCH(f::pipe(childToParent1, childToParent2));

    p pid = p::fork();
    switch(pid) {
    case -1:
      ux::Error(errno, EC_RESOURCE);
    case 0: // child.

      parentToChild1.dup2(STDIN_FILENO);
      childToParent2.dup2(STDOUT_FILENO);
      parentToChild2.close();
      childToParent1.close();

      EC_CATCH(p::execlp(path));
      parentToChild1.close();
      childToParent2.close();
    default: // parent.

      parentToChild1.close();
      childToParent2.close();
      fmt::print("{}\n", childToParent2);
      fmt::print("{}\n", parentToChild1);
      fromEngine = ::fdopen(childToParent1, "r");
      toEngine = ::fdopen(parentToChild2, "w");

      init();
    }
  };

  p ChessEngine::wait() {
    return p::wait(m_child_process);
  }

  /*
 * Wait for the given response from the engine.
 * Return true on success or false on failure (EOF).
 */
  bool ChessEngine::waitForResponse(const char* str) {
    bool eof = false;
    std::string response;
    do {
      response = getResponse(eof);
    } while(strcmp(str, response.c_str()) != 0 && !eof);
    return strcmp(str, response.c_str()) == 0;
  }

  /*
 * Read and return a single line of response from the engine.
 * Set eof if the end of file is reached.
 */
  std::string ChessEngine::getResponse(bool& eof) {
    const int MAXBUFF = 100;
    // Since the reads are not guaranteed to be line-based, buffer retains
    // text read but not returned on a previous call.
    static char buffer[MAXBUFF + 1] = "";
    // What is returned.
    std::string result;
    bool endOfLine = false;

    //cout << "# get response" << endl;
    eof = false;
    while(!endOfLine && !eof) {

      if(*buffer == '\0') {

        char* readResult = ::fgets(buffer, MAXBUFF, fromEngine);

        if(readResult == NULL) {
          eof = true;
        }
      }
      if(!eof) {

        // Look for the end of the line, which might not have been read.
        // NB: There is a boundary error possible here, where a \n\r combination
        // is split across two reads. If that happens then the second char will be
        // treated as a spurious blank line.
        int index = 0;
        char ch = buffer[index];
        while(ch != '\0' && ch != '\n' && ch != '\r') {
          index++;
          ch = buffer[index];
        }
        if(ch == '\n' || ch == '\r') {
          endOfLine = true;
          buffer[index] = '\0';
          index++;
          char nextChar = buffer[index];
          if(nextChar == '\n' || nextChar == '\r') {
            index++;
          }
        }
        // Concatenate up to the end of line, or everything if not
        // at the end of the line.
        result += buffer;
        // Retain any left.
        if(endOfLine) {

          strcpy(buffer, &buffer[index]);
        }
        else {
          *buffer = '\0';
        }
      }
    }
    if(!eof) {
      //fmt::print("eooofff\n");
      //cout << "# [" << result << "]" << endl;
    }
    return result;
  }

  void ChessEngine::quit() {
    send("quit");
  }

  void ChessEngine::isready() {
    send("isready");
  }

  /*
 * API 2
 */
  void ChessEngine::send(const std::string& str) {
    send(str.c_str());
  }
  /*
 * Send the given string to the engine.
 */
  void ChessEngine::send(const char* str) {

    fprintf(toEngine, "%s\n", str);
    fflush(toEngine);
  }

  /* Look for "id name" in the engine's initial output and use it
 * to set the engine's identity.
 */
  bool ChessEngine::setIdentity() {
    // Get the identity.
    const char* id_prefix = "id name ";
    bool eof, identitySet = false;

    do {
      fmt::print("heyyy!\n");
      std::string idResponse = getResponse(eof);
      fmt::print("{}\n", idResponse);
      if(!eof) {
        if(idResponse.find(id_prefix) == 0) {
          this->identity = idResponse.substr(strlen(id_prefix));
          identitySet = true;
        }
      }
    } while(!identitySet && !eof);
    return identitySet;
  }

  void ChessEngine::getOptions() {
    // Get the identity.
    send("uci");
    bool eof = false;

    do {
      std::string line = getResponse(eof);
      auto tokens = split_s(line, ' ');
      if(!eof) {
        if(tokens.size() != 0) {
          if(tokens[0] == "uciok") {
            eof = true;
          }
          else {
            // Capture id.
            if(tokens[0] == "id" && tokens[1] == "name") {
              m_id.first = tokens.at(2);
              m_id.second = tokens.at(3);
              fmt::print("id: {}\n", line);
            }
            if(tokens[0] == "option") {
              //no op
              fmt::print("op: {}\n", line);
            }
          }
        }
      }
    } while(!eof);
  }

  /*
 * Check that the engine is ready.
 */
  bool ChessEngine::checkIsReady() {
    send("isready");

    if(waitForResponse("readyok")) {
      return true;
    }
    else {
      return false;
    }
    // return !eof && response.compare("readyok") == 0;
  }

  void ChessEngine::go(int searchDepth) {
    std::stringstream ss;
    ss << "go depth " << searchDepth;
    send(ss.str());
  }

  void ChessEngine::setPosition(const std::string& moves, const std::string& fenstring) {
    if(fenstring.length() == 0) {
      setFENPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", moves);
    }
    else {
      setFENPosition(fenstring, moves);
    }
  }

  void ChessEngine::setFENPosition(const std::string& fenstring, const std::string& moves) {
    std::stringstream ss;
    if(moves.length() == 0) {
      ss << "position fen " << fenstring;
      send(ss.str());
    }
    else {
      ss << "position fen " << fenstring << " moves " + moves;
      send(ss.str());
    }
  }

  /*
 * Send a setoption command to the engine using the
 * given name and value.
 */
  void ChessEngine::setOption(const std::string& name, const std::string& value) {
    std::stringstream ss;
    ss << "setoption name " << name << " value " << value;
    send(ss.str());
  }

  /*
 * Send a setoption command to the engine using the
 * given name and value.
 */
  void ChessEngine::setOption(const std::string& name, int value) {
    std::stringstream ss;
    ss << value;
    setOption(name, ss.str());
  }

  // void ChessEngine::setOptions(std::map<std::string, std::string>& options) {
  //   std::map<std::string, std::string>::iterator it;
  //   for(it = options.begin(); it != options.end(); it++) {
  //     setOption(it->first, it->second);
  //   }
  // }

  bool ChessEngine::init() {
    // this->variations = variations;

    getOptions();

    return true;
    // send("uci");
    // // printf("hallo outside da loop");
    // if(!setIdentity()) {
    //   std::cerr << "Failed to identify the engine." << std::endl;
    //   std::cerr << "No \"id name\" found." << std::endl;
    //   return false;
    // }
    // else if(waitForResponse("uciok")) {
    //   getOptions();
    //   // setOption("UCI_AnalyseMode", "true");
    //   // setOption("MultiPV", variations);

    //   // Set command-line options.
    //   //setOptions(options);

    //   return checkIsReady();
    // }
    // else {
    //   return false;
    // }
  }

  /*
 * Tokenise text into tokens.
 * tokens is not cleared by this function.
 */
  void tokenise(std::string& text, std::vector<std::string>& tokens) {
    std::stringstream ss(text);
    std::string token;
    // printf("token: %s\n", token.c_str());
    while(getline(ss, token, ' ')) {
      if(token != "") {
        tokens.push_back(token);
      }
    }
  }

  /*
 * Extract the information from an info line returned
 * by the engine.
 */
  void extractInfo(std::string& info, std::vector<std::string> infoTokens) {

    if("info" != infoTokens[0]) {
      throw std::runtime_error("tokens doesnt have info");
    };
    if((info.find("multipv ") != std::string::npos) || (info.find("nodes ") != std::string::npos)) {
      if((info.find("cp ") != std::string::npos)) {
        int numTokens = infoTokens.size();
        int t = 1;
        while(t < numTokens && infoTokens[t] != "depth") {
          t++;
        }
        if(t < numTokens) {
          int depth = std::stoi(infoTokens[t + 1]);
          //  if(depth == searchDepth) {
          fmt::print("{}\n", info);
          //Evaluation* ev = new Evaluation(infoTokens, info);
          //saveEvaluation(ev, info);
          //}
        }
      }
    }
  }

  void ChessEngine::obtainEvaluations(void) {
    std::string reply;
    std::vector<std::string> tokens;
    bool bestMoveFound = false;
    bool eof = false;

    do {

      reply = getResponse(eof);
      // debug("reply: %s", reply.c_str());
      // debug("reply size: %d", reply.size());
      // debug("not eof? %s", !eof ? "true" : "false");
      tokens.clear();
      tokenise(reply, tokens);
      std::string tokenType = tokens[0];
      if(!eof && reply.size() > 13) {
        if(tokenType == "info") {
          extractInfo(reply, tokens);
        }
        else if(tokenType == "bestmove") {
          bestMoveFound = true;
        }
      }
      else if(!eof && tokenType == "bestmove") {
        bestMoveFound = true;
      }
    } while(!bestMoveFound && !eof);
  }

  std::string ChessEngine::bestMove() {
    go(10);
    std::string reply;
    std::string bestmove;
    std::vector<std::string> tokens;
    bool bestMoveFound = false;
    bool eof = false;

    do {

      reply = getResponse(eof);
      // debug("reply: %s", reply.c_str());
      // debug("reply size: %d", reply.size());
      // debug("not eof? %s", !eof ? "true" : "false");
      tokens.clear();
      tokenise(reply, tokens);
      std::string tokenType = tokens[0];
      if(!eof && reply.size() > 13) {
        if(tokenType == "info") {
          extractInfo(reply, tokens);
        }
        else if(tokenType == "bestmove") {
          bestmove = tokens[1];
          bestMoveFound = true;
        }
      }
      else if(!eof && tokenType == "bestmove") {
        bestmove = tokens[1];
        bestMoveFound = true;
      }
    } while(!bestMoveFound && !eof);
    return bestmove;
  }

} // namespace ucichess