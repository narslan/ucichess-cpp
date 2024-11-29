#include "../../src/ucichess/ux/ux.hpp"
#include <cstdlib>
#include <string>
#include <string_view>
#include <sys/socket.h>
#include <unistd.h>

constexpr std::string SOCKETNAME = "MySocket";

int main(int argc, const char** argv) {

  ::unlink(SOCKETNAME.c_str());
  //we create a unix socket.

  ux::SockAddrUn sa{SOCKETNAME.c_str()};

  if(ux::Process::fork()) { /* in child*/
    ux::Socket fd_skt{};
    fd_skt.socket();
    fd_skt.connect(sa);
    std::string h{"Hello"};
    fd_skt.write(h.c_str(), h.size());
    char buf[100];
    fd_skt.read(buf, sizeof(buf));
    fmt::print("client got: {}\n", buf);
    exit(EXIT_SUCCESS);
  }
  else { /*in parent*/
    ux::Socket fd_skt{};
    fd_skt.socket();
    fd_skt.bind(sa);
    fd_skt.listen(SOMAXCONN);
    auto sock_clt = fd_skt.accept();
    char buf[100];

    sock_clt.read(buf, sizeof(buf));
    fmt::print("server got: {}\n", buf);

    std::string h{"Good bye"};
    sock_clt.write(h.c_str(), h.size());
    sock_clt.close();
    fd_skt.close();
    exit(EXIT_SUCCESS);
  }

  return 0;
}