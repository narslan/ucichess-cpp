#include "../../src/ucichess/ux/ux.hpp"
#include <sys/select.h>
const char* SOCKETNAME = "MySocket";

bool run_server(ux::SockAddrUn& sa) {

  ux::Socket fd_skt{};
  fd_skt.socket();
  fd_skt.bind(sa);
  fd_skt.listen(SOMAXCONN);

  //for select;
  fd_set set, read_set;
  FD_ZERO(&set);
  FD_SET(fd_skt.fd, &set);

  while(true) {
    read_set = set;
  }
};
int main(int argc, const char** argv) {

  ux::SockAddrUn sa{SOCKETNAME};

  return 0;
}