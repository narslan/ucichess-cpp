#pragma once
#include <cstdio>
#include <poll.h>
#include <sys/uio.h>
#include <utime.h>
namespace ux {
  class File {
    public:
    ~File() = default;

    File(int f = -1, const char* p = nullptr, ssize_t s = -1)
        : fd(f)
        , path(p)
        , size(s) { }
    File(const char* p, ssize_t s = -1)
        : fd(-1)
        , path(p)
        , size(s) { }
    void set(int f = -1, char* p = nullptr, ssize_t s = -1) {
      fd = f;
      path = p;
      size = s;
    }
    void set(char* p, ssize_t s = -1) {
      fd = -1;
      path = p;
      size = s;
    }

    void close(void);
    File dup(void);
    File dup2(int fd2);
    static void pipe(File pf[2]);
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

    // to enable comparing File objects with int handles.
    bool operator<(const int& rhs);
    bool operator>(const int& rhs);
    bool operator==(const int& rhs);

    File& operator++();
    File operator++(int);
    int fd;
    const char* path;
    ssize_t size;
  };

} // namespace ux