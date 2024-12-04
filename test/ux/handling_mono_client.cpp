#include "../../src/ucichess/ux/process.hpp"
#include "../../src/ucichess/ux/socket.hpp"
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>

const char* SOCKETNAME = "MySocket";

int main(int argc, const char** argv) {

  ::unlink(SOCKETNAME);
  //we create a unix socket.

  ux::SockAddrUn sa{SOCKETNAME};

  if(ux::Process::fork() == 0) { /* in child*/
    ux::Socket fd_skt{-1};
    fd_skt.socket();
    fd_skt.connect(sa);
    std::string h{"Hello"};
    fd_skt.write(h.c_str(), h.size() + 1);
    char buf[100];
    fd_skt.read(buf, sizeof(buf));
    fmt::print("client got: {}\n", buf);
    exit(EXIT_SUCCESS);
  }
  else { /*in parent*/
    ux::Socket fd_skt{-1};
    fd_skt.socket();
    fd_skt.bind(sa);
    fd_skt.listen(SOMAXCONN);
    auto sock_clt = fd_skt.accept();
    char buf[100];

    sock_clt.read(buf, sizeof(buf));
    fmt::print("server got: {}\n", buf);

    std::string h{"Good bye"};
    sock_clt.write(h.c_str(), h.size() + 1);
    sock_clt.close();
    fd_skt.close();
    exit(EXIT_SUCCESS);
  }

  return 0;
}