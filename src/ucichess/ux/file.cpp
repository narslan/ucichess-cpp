#include "file.hpp"
#include "../error/error.hpp"
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>
namespace ux {
  /**
	Calls pipe.
*/
  /* static */
  void File::pipe(File pf[2]) {
    int pfd[2];

    if(::pipe(pfd) == -1)
      throw Error(errno);
    pf[0].set(pfd[0]);
    pf[1].set(pfd[1]);
  }

  /**
	Calls close.
*/
  void File::close(void) {
    if(::close(fd) == -1)
      throw Error(errno);
  }

  /**
	Calls dup.
*/
  File File::dup(void) {
    int fd2;

    if((fd2 = ::dup(fd)) == -1)
      throw Error(errno);
    return File(fd2);
  }

  /**
	Calls dup2.
*/
  File File::dup2(int fd2) {
    if(::dup2(fd, fd2) == -1)
      throw Error(errno);
    return File(fd2);
  }

  /**
	Calls read or pread.
*/
  ssize_t File::read(void* buf, size_t nbytes, off_t offset) {
    ssize_t n;

    if(offset == -1)
      n = ::read(fd, buf, nbytes);
    else
      n = ::pread(fd, buf, nbytes, offset);
    if(n == -1)
      throw Error(errno);
    return n;
  }

  /**
	Calls readv.
*/
  ssize_t File::readv(const struct iovec* iov, int iovcnt) {
    ssize_t n;

    if((n = ::readv(fd, iov, iovcnt)) == -1)
      throw Error(errno);
    return n;
  }

  /**
	Calls write or pwrite.
*/
  ssize_t File::write(const void* buf, size_t nbytes, off_t offset) {
    ssize_t n;

    if(offset == -1)
      n = ::write(fd, buf, nbytes);
    else
      n = ::pwrite(fd, buf, nbytes, offset);
    if(n == -1)
      throw Error(errno);
    return n;
  }

  /**
	Calls writev.
*/
  ssize_t File::writev(const struct iovec* iov, int iovcnt) {
    ssize_t n;

    if((n = ::writev(fd, iov, iovcnt)) == -1)
      throw Error(errno);
    return n;
  }
  /**
	Calls select.
*/
  /* static */ int
  select(int nfds, fd_set* readset, fd_set* writeset, fd_set* errorset, struct timeval* timeout) {
    int r;

    if((r = ::select(nfds, readset, writeset, errorset, timeout)) == -1)
      throw Error(errno);
    return r;
  }

  /**
	Calls pselect.
*/
  /* static */ int pselect(int nfds,
                           fd_set* readset,
                           fd_set* writeset,
                           fd_set* errorset,
                           const struct timespec* timeout,
                           const sigset_t* sigmask) {
    int r;

    if((r = ::pselect(nfds, readset, writeset, errorset, timeout, sigmask)) == -1)
      throw Error(errno);
    return r;
  }
  /**
	Calls poll.
*/
  /* static */ int poll(struct pollfd fdinfo[], nfds_t nfds, int timeout) {
    int r;

    if((r = ::poll(fdinfo, nfds, timeout)) == -1)
      throw Error(errno);
    return r;
  }

  bool File::operator<(const int& rhs) {
    return fd < rhs;
  };
  bool File::operator>(const int& rhs) {
    return fd > rhs;
  };
  bool File::operator==(const int& rhs) {
    return fd == rhs;
  };
  //From https://en.cppreference.com/w/cpp/language/operators
  // prefix increment
  File& File::operator++() {
    fd++;
    return *this;
  }

  // postfix increment
  File File::operator++(int) {
    File old = *this; // copy old value
    operator++(); // prefix increment
    return old; // return old value
  }

} // namespace ux