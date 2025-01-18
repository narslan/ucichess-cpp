#include "engine.hpp"
#include "../error/error.hpp"

#include <algorithm>
#include <cstring>
#include <fcntl.h>

#include <fmt/core.h>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std::string_literals;

namespace ucichess {
  // split_s is the core machinery. It split s at splitPoint, and returns a vector.
  std::vector<std::string> split_s(std::string const& s, char delimeter) {
    std::vector<std::string> elements;
    std::stringstream string_stream(s);
    std::string item;
    while(std::getline(string_stream, item, delimeter)) {
      elements.push_back(item);
    }
    return elements;
  }

  ChessEngine::ChessEngine(std::string const& path)
      : m_path{path} {
    ux::File parentToChild1;
    ux::File parentToChild2;
    ux::File childToParent1;
    ux::File childToParent2;

    EC_CATCH(f::pipe(parentToChild1, parentToChild2));
    EC_CATCH(f::pipe(childToParent1, childToParent2));

    p pid = p::fork();
    switch(pid) {
    case -1: ux::Error(errno, EC_RESOURCE);
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
      // fmt::print("{}\n", childToParent2);
      // fmt::print("{}\n", parentToChild1);
      fromEngine = ::fdopen(childToParent1, "r");
      toEngine = ::fdopen(parentToChild2, "w");
      m_child_process = pid;
      getOptions();
    }
  };

  p ChessEngine::wait() {
    return p::wait(m_child_process);
  }

  std::pair<std::string, std::string> ChessEngine::id() {
    return m_id;
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

    return result;
  }

  void ChessEngine::quit() {
    send("quit"s);
  }

  void ChessEngine::isready() {
    send("isread");
  }

  void ChessEngine::send(std::string const& str) {

    fprintf(toEngine, "%s\n", str.c_str());
    fflush(toEngine);
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
    return false;
  }

  /*
 * Send ucinewgame if a new game happens.
 */
  bool ChessEngine::newGame() {
    send("ucinewgame");
    return checkIsReady();
  }

  void ChessEngine::go(int searchDepth) {
    std::stringstream ss;
    ss << "go depth " << searchDepth;
    send(ss.str());
  }

  void ChessEngine::setPosition(const std::string& fen, const std::string& moves) {
    std::stringstream ss;

    if(fen == "") {
      ss << "position startpos";
      send(ss.str());
      return;
    }

    if(moves.length() == 0) {
      ss << "position fen " << fen;
      send(ss.str());
    }
    else {
      ss << "position fen " << fen << " moves " + moves;
      send(ss.str());
    }
  }

  /*
 * Tokenise text into tokens.
 * 
 */
  std::vector<std::string> tokenise(std::string& text) {

    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;

    while(getline(ss, token, ' ')) {
      if(token != "") {
        tokens.push_back(token);
      }
    }
    return tokens;
  }

  /*
   * Extract the information from an info line returned
   * by the engine.
   */
  std::tuple<std::string, std::string> extractInfo(std::vector<std::string>& infoTokens) {

    std::string score;
    std::string depth;
    
    auto it = std::find(infoTokens.begin(), infoTokens.end(), "cp");

    if (it != infoTokens.end()) {
      score = ++*it;
    }
        

    auto it = std::find(infoTokens.begin(), infoTokens.end(), "depth");

    if (it != infoTokens.end()) {
      depth = ++*it;
    }
    
    return std::make_tuple(score, depth);
  }

  std::string ChessEngine::bestMove(int depth) {
    go(depth);

    std::string bestmove;
    //std::vector<std::string> eval;
    bool bestMoveFound = false;
    bool eof = false;
    do {

      auto reply = getResponse(eof);
      auto tokens = tokenise(reply);

      std::string tokenType = tokens[0];

      //    if(tokenType == "info") {
      //  eval = tokens;
      // }
      //else
      if(tokenType == "bestmove") {
        bestmove = tokens[1];
        bestMoveFound = true;
      }

    } while(!bestMoveFound && !eof);

    std::string seldepth, score;

    //std::tie(seldepth, score) = extractInfo(eval);
    //return std::make_tuple(seldepth, score, bestmove);
    return bestmove;
  }

  std::tuple<std::string, std::string, std::string> ChessEngine::analyze(int depth) {
    go(depth);
    
    std::string bestmove;
    //std::vector<std::string> eval;
    bool bestMoveFound = false;
    bool eof = false;
    do {

      auto reply = getResponse(eof);
      auto tokens = tokenise(reply);

      std::string tokenType = tokens[0];

         if(tokenType == "info") {
           eval = tokens;
         }
         else
           if(tokenType == "bestmove") {
             bestmove = tokens[1];
             bestMoveFound = true;
           }
    } while(!bestMoveFound && !eof);

    std::string seldepth, score;

    std::tie(seldepth, score) = extractInfo(eval);
    return std::make_tuple(seldepth, score, bestmove);
    
  }

} // namespace ucichess
