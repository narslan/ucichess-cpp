#pragma once

#include "../ux/file.hpp"
#include "../ux/process.hpp"

#include <string>

#include <sstream>

namespace ucichess {
  using f = ux::File;
  using p = ux::Process;

  class ChessEngine {
    public:
    ChessEngine(const std::string& path);
    ~ChessEngine() {
      quit();
    };

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

    //void setOptions(std::map<std::string, std::string>& options);
    void obtainEvaluations();
    void getOptions();
    std::string bestMove();
    void isready();

    void quit();
    std::pair<std::string, std::string> id();

    private:
    // private member functions.

    bool init();

    //members.

    std::string m_path;
    //std::unordered_map<std::string, std::string> options;

    // m_id represents an id like Stockfish dev-20230218-037ef3e1.
    // It constructed in getOptions(). It is the version of the engine.
    std::pair<std::string, std::string> m_id;

    p m_child_process;

    FILE* fromEngine;
    FILE* toEngine;
  };

} // namespace ucichess
