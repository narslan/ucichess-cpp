#pragma once
#include <cstdio>
#include <poll.h>
#include <sys/select.h>
#include <sys/uio.h>

#include <utime.h>
namespace ux {
  class File {
    protected:
    int fd_;

    public:
    ~File() {
      if(fd_ != -1) {
        close();
      }
    };

    // namespace ux

    explicit File(int f)
        : fd_(f) { }

    void set(int f) {
      fd_ = f;
    }

    File(const File&) = delete;
    File& operator=(const File&) = delete;
    bool ok() const {
      return fd_ != -1;
    }

    operator int() const {
      return fd_;
    }

    void close(void);
    File dup(void);
    File dup2(int fd2);
    static void pipe(File& pf1, File& pf2);
    ssize_t read(void* buf, size_t nbytes, off_t offset = -1);
    ssize_t readv(const struct iovec* iov, int iovcnt);

    ssize_t write(const void* buf, size_t nbytes, off_t offset = -1);
    ssize_t writev(const struct iovec* iov, int iovcnt);

    static int select(int nfds,
                      fd_set* readset,
                      fd_set* writeset = NULL,
                      fd_set* errorset = NULL,
                      struct timeval* timeout = NULL);
    static int pselect(int nfds,
                       fd_set* readset,
                       fd_set* writeset = NULL,
                       fd_set* errorset = NULL,
                       const struct timespec* timeout = NULL,
                       const sigset_t* sigmask = NULL);
    static int poll(struct pollfd fdinfo[], nfds_t nfds, int timeout = -1);
  };

} // namespace ux