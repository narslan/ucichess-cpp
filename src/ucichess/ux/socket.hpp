#pragma once

#include "file.hpp"
#include <arpa/inet.h>
#include <cstddef>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace ux {

  /**
	\ingroup ux
*/
  class SockIPv4 {
    protected:
    in_addr_t ipv4;

    public:
    SockIPv4(in_addr_t ip = 0) {
      set(ip);
    }
    SockIPv4(const char* str) {
      set(str);
    }
    void set(const char* str);
    void set(in_addr_t ip = 0) {
      ipv4 = ip;
    }
    in_addr_t get_ipv4(void) const {
      return ipv4;
    }
    const char* get_string(char* buf, socklen_t bufsize) const;
  };

  /**
	\ingroup ux
*/
  class SockIPv6 {
    protected:
    uint8_t ipv6[16];

    public:
    SockIPv6(uint8_t* ip = NULL) {
      set(ip);
    }
    SockIPv6(const char* str) {
      set(str);
    }
    void set(const char* str);
    void set(uint8_t*);
    const uint8_t* get_ipv6(void) const {
      return ipv6;
    }
    const char* get_string(char* buf, socklen_t bufsize) const;
  };

  class SockAddr {
    protected:
    struct sockaddr_storage sa_storage;
    socklen_t sa_len;
    int sa_protocol;

    public:
    SockAddr(void)
        : sa_len(0)
        , sa_protocol(0) { }
    const struct sockaddr* get_addr(void) const {
      return (const struct sockaddr*)&sa_storage;
    }
    struct sockaddr* get_addr(void) {
      return (struct sockaddr*)&sa_storage;
    }
    socklen_t get_len(void) const {
      return sa_len;
    }
    socklen_t* get_len_ptr(void) {
      return &sa_len;
    }
    void set_len(socklen_t len) {
      sa_len = len;
    }
    void set_protocol(int protocol) {
      sa_protocol = protocol;
    }
    int get_protocol(void) {
      return sa_protocol;
    }
    static void getaddrinfo(const char* nodename,
                            const char* servname,
                            const struct addrinfo* hint,
                            struct addrinfo** infop);
    static void getaddrinfo(const char* nodename,
                            const char* servname,
                            int family,
                            int type,
                            int flags,
                            struct addrinfo** infop);
    static void freeaddrinfo(struct addrinfo* infop) {
      ::freeaddrinfo(infop);
    }
    void set_server(const char* nodename, const char* servname = "80");
    static void getnameinfo(const struct sockaddr* sa,
                            socklen_t sa_len,
                            char* nodename,
                            socklen_t nodelen,
                            char* servname,
                            socklen_t servlen,
                            unsigned flags);
  };

  /**
	\ingroup Ux
*/
  class SockAddrUn : public SockAddr {
    public:
    SockAddrUn(const char* path = "") {
      set(path);
    }
    void set(const char* path = "");
  };

  /**
	\ingroup Ux
*/
  class SockAddrIn : public SockAddr {
    public:
    SockAddrIn(in_port_t port, struct in_addr& sa) {
      set(port, sa);
    }
    SockAddrIn(in_port_t port, in_addr_t ipv4) {
      set(port, ipv4);
    }
    SockAddrIn(in_port_t port, const char* dotted) {
      set(port, dotted);
    }
    void set(in_port_t port, struct in_addr& sa);
    void set(in_port_t port, in_addr_t ipv4);
    void set(in_port_t port, const char* dotted);
  };
  class Socket : public File {

    public:
    Socket(int f = -1, const char* p = NULL, ssize_t s = -1)
        : File(f, p, s) { }
    Socket(const char* p, ssize_t s = -1)
        : File(-1, p, s) { }
    Socket accept(SockAddr* sa = NULL);
    void connect(const SockAddr& sa);
    void bind(const SockAddr& sa);
    void getpeername(SockAddr& sa);
    void getsockname(SockAddr& sa);
    void getsockopt(int level, int option, void* value, socklen_t& value_len);
    void listen(int backlog = SOMAXCONN);
    ssize_t recv(void* buffer, size_t length, int flags);
    ssize_t
    recvfrom(void* buffer, size_t length, int flags, struct sockaddr* sa, socklen_t* sa_len);
    ssize_t recvmsg(struct msghdr* message, int flags);
    ssize_t send(const void* data, size_t length, int flags);
    ssize_t sendmsg(const struct msghdr* message, int flags);
    ssize_t sendto(
        const void* message, size_t length, int flags, const struct sockaddr* sa, socklen_t sa_len);
    void setsockopt(int level, int option, const void* value, socklen_t value_len);
    void shutdown(int how);
    bool sockatmark(void);
    void socket(int domain = AF_UNIX, int type = SOCK_STREAM, int protocol = 0);
    static void
    socketpair(Socket sv[2], int domain = AF_UNIX, int type = SOCK_STREAM, int protocol = 0);
  };

} // namespace ux
