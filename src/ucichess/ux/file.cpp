#include "file.hpp"
#include "../error/error.hpp"
#include <fcntl.h>
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

} // namespace ux