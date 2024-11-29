#include "process.hpp"
#include "../error/error.hpp"
#include <unistd.h>

namespace ux {

  uid_t Process::getuid(void) {
    return ::getuid();
  }

  // Get process id.
  pid_t Process::getpid() {
    return ::getpid();
  }

  pid_t Process::getpgid(pid_t pid) {
    pid_t rtn_pid;

    if((rtn_pid = ::getpgid(pid)) == -1)
      throw;
    return rtn_pid;
  }

  Process Process::fork() {
    {

      pid_t rtn_pid;

      if((rtn_pid = ::fork()) == -1)
        throw Error(errno);
      return Process(rtn_pid);
    }
  }

  /* static */
  void Process::waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options) {
    if(::waitid(idtype, id, infop, options) == -1)
      throw Error(errno);
  }

  pid_t Process::waitpid(pid_t pid, int options) {
    pid_t rtn_pid;
    int status;

    if((rtn_pid = ::waitpid(pid, &status, options)) == -1)
      throw Error(errno, EC_RESOURCE);

    return rtn_pid;
  }

} // namespace ux
