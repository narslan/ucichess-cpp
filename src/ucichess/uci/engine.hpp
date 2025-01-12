#pragma once

#include "../ux/file.hpp"
#include "../ux/process.hpp"

#include <string>

#include <sstream>

namespace ucichess {
  using f = ux::File;
  using p = ux::Process;

  struct Evaluation {
    std::string score;
    std::string depth;
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
    void setPosition(const std::string& fen, const std::string& moves);

    template <typename T>
    void setOption(const std::string& key, T value) {
      std::stringstream ss;
      ss << "setoption name " << key << " value " << value;
      send(ss.str());
    };

    void getOptions();
    //    std::tuple<std::string, std::string, std::string> bestMove(int);
    std::string bestMove(int);
    void isready();

    bool newGame();
    void quit();
    std::pair<std::string, std::string> id();

    private:
    // private member functions.

    bool init();

    //members.

    std::string m_path;
    std::pair<std::string, std::string> m_id;

    p m_child_process;

    FILE* fromEngine;
    FILE* toEngine;

  }; // namespace ucichess
} // namespace ucichess
