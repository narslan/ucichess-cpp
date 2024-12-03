#pragma once

#include "../ux/ux.hpp"

#include <map>
#include <string>

namespace ucichess {
  using f = ux::File;
  using p = ux::Process;

  class ChessEngine {
    public:
    ChessEngine(const std::string& path);
    ~ChessEngine() = default;

    p wait();

    //API 2:
    void go();
    bool waitForResponse(const char* str);
    std::string getResponse(bool& eof);
    bool initEngine(int searchDepth, std::map<std::string, std::string>& options);
    void send(const std::string& str);
    void send(const char* str);
    bool setIdentity();
    bool checkIsReady();
    void setPosition(const std::string& moves, const std::string& fenstring);
    void setFENPosition(const std::string& fenstring, const std::string& moves);
    void setOption(const std::string& name, const std::string& value);
    void setOption(const std::string& name, int value);
    void setOptions(std::map<std::string, std::string>& options);
    void obtainEvaluations(void);
    std::string bestMove();
    void isready();

    std::string identity;
    void quit();

    private:
    std::string m_path;

    int searchDepth;
    p m_child_process;
    f m_pipe_write; // write part, todo, remove
    f m_pipe_read; // read part, todo remove
    FILE* fromEngine;
    FILE* toEngine;
  };

} // namespace ucichess