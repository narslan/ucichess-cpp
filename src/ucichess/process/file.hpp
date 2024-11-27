#pragma once
#include <cstdio>
namespace ucichess {
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
    ssize_t write(const void* buf, size_t nbytes, off_t offset = -1);

    int fd;
    const char* path;
    ssize_t size;
  };

} // namespace ucichess