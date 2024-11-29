#pragma once

#include "../error/error.hpp"
#include <fmt/core.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace ux {

  class Process {
    protected:
    pid_t pid;

    public:
    Process(pid_t id = -1)
        : pid(id == -1 ? getpid() : id) { }

    void set(pid_t id) {
      pid = id;
    }

    operator pid_t() {
      return pid;
    }

    static pid_t getpid();
    static pid_t getpgid(pid_t pid);
    static uid_t getuid();

    // Fork creates a new process.
    static Process fork();

    /**
		Calls ::wait.
	*/
    static pid_t wait() {
      return Process::waitpid(-1);
    }

    static pid_t wait(int who) {
      return Process::waitpid(who);
    }

    static void waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options = 0);
    static pid_t waitpid(pid_t pid, int options = 0);
    // Exec family of calls.

    template <typename... Args>
    static void execlp(std::string path, Args... args) {
      try {
        ::execlp(path.c_str(), path.c_str(), args..., (char*)nullptr);
        throw Error(errno, EC_RESOURCE);
      }
      catch(const std::exception& err) {
        fmt::print("err: {}\n", err.what());
      }
    }

    template <typename... Args>
    static void execvpe(std::string path, char* const* envp, Args... args) {
      std::vector<std::string> s;
      (s.push_back(std::forward<Args>(args)), ...);

      char** argv = new char*[s.size()];

      for(size_t i = 0; i < s.size(); i++) {
        argv[i] = (char*)s[i].c_str();
      }

      try {
        ::execvpe(path.c_str(), argv, envp);
        throw Error(errno, EC_RESOURCE);
      }
      catch(const std::exception& err) {
        fmt::print("{}\n", err.what());
      }
    }

    template <typename... Args>
    static void execute(std::string path, char* const* envp, Args... args) {

      pid_t pid = fork();
      switch(pid) {
      case -1: /*Parent error*/
        throw "Fork failed";
      case 0: /* Child*/
        execvpe(path, envp, args...);
      default:
        wait(pid);
      }
    }

    template <typename... Args>
    static void execute2(std::string path, Args... args) {

      pid_t pid = fork();
      switch(pid) {
      case -1: /*Parent error*/
        throw "Fork failed";
      case 0: /* Child*/
        execlp(path, args...);
      default:
        wait(pid);
        //waitid(P_ALL, pid, nullptr, 0);
      }
    }

    ~Process() = default;
  };

} // namespace ux