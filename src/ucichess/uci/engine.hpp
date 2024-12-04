#pragma once

#include "../ux/file.hpp"
#include "../ux/process.hpp"

#include <string>
#include <unordered_map>

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

    void send(const std::string& str);
    void send(const char* str);
    bool setIdentity();
    bool checkIsReady();
    void setPosition(const std::string& moves, const std::string& fenstring);
    void setFENPosition(const std::string& fenstring, const std::string& moves);
    void setOption(const std::string& name, const std::string& value);
    void setOption(const std::string& name, int value);
    //void setOptions(std::map<std::string, std::string>& options);
    void obtainEvaluations();
    void getOptions();
    std::string bestMove();
    void isready();

    std::string identity;
    void quit();

    private:
    // private member functions.

    bool init();

    //members.

    std::string m_path;
    std::unordered_map<std::string, std::string> options;

    p m_child_process;

    FILE* fromEngine;
    FILE* toEngine;
  };

} // namespace ucichess