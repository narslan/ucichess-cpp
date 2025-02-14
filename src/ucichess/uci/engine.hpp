#pragma once

#include "../ux/file.hpp"
#include "../ux/process.hpp"

#include <string>

#include <sstream>

namespace ucichess {
  using f = ux::File;
  using p = ux::Process;

  struct Evaluation {
    std::string seldepth;
    std::string multipv;
    std::string score;
    std::string nodes;
    std::string time;
    std::string bestmove;
  };

  class ChessEngine {
    public:
    // Constructors && public members

    ChessEngine(const std::string& path);
    ~ChessEngine() {
      quit();
    };

    // wait for the child.
    p wait();

    //API 2:
    void go(int searchDepth);
    bool waitForResponse(const char* str);
    std::string getResponse(bool& eof);

    void send(std::string const& str);

    bool checkIsReady();
    void setPosition(const std::string& fen);
   
    std::vector<Evaluation> analyze(int depth);
    
    void getOptions();
    void isready();
    bool newGame();
    void quit();
    void multipv(int);
    void threads(int);
    void hash(int);
    
    std::string bestMove(int);
    std::pair<std::string, std::string> id();

    template <typename T>
    void setOption(const std::string& key, T value) {
      std::stringstream ss;
      ss << "setoption name " << key << " value " << value;
      send(ss.str());
    };
    
    private:
    // methods.
    bool init();

    // members.
    std::string m_path;
    std::pair<std::string, std::string> m_id;

    p m_child_process;

    FILE* fromEngine;
    FILE* toEngine;

  }; // namespace ucichess
} // namespace ucichess
