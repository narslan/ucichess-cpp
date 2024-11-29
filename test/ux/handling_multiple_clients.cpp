#include "../../src/ucichess/ux/ux.hpp"
#include <sys/select.h>
const char* SOCKETNAME = "MySocket";

bool run_server(ux::SockAddrUn& sa) {

  int fd; //?
  int fd_hwm; //?
  ux::Socket fd_client;
  ux::Socket fd_skt{};
  fd_skt.socket();
  fd_skt.bind(sa);
  fd_skt.listen(SOMAXCONN);

  if(fd_skt > fd_hwm)
    fd_hwm = fd_skt.fd;
  //for select;
  fd_set set, read_set;
  FD_ZERO(&set);
  FD_SET(fd_skt.fd, &set);

  while(true) {
    read_set = set;
    ux::File::select(fd_hwm + 1, &read_set, nullptr, nullptr);
    for(ux::File fd = 0; fd < fd_hwm; fd++) {
      if(FD_ISSET(fd.fd, &read_set)) {
        if(fd == fd_skt.fd) {
          fd_client = fd_skt.accept();
          FD_SET(fd_client.fd, &set);
          if(fd_client > fd_hwm)
            fd_hwm = fd_client.fd;
        }
      }
      else {
        char buf[100];
        int nread = fd.read(buf, sizeof(buf));
        if(nread == 0) {
          FD_CLR(fd.fd, &set);
          if(fd == fd_hwm)
            fd_hwm--;
          fd.close();
        }
        else {
          fmt::print("server got: '{}'\n", buf);
          fd.write("goodbye!", 9);
        }
      }
    }
  }
  fd_skt.close();
  return true;
};

static bool run_client(ux::SockAddrUn& sa) {
  if(ux::Process::fork() == 0) {
    ux::Socket fd_skt{};
    char buf[100];
    fd_skt.socket();

    while(fd_skt.connect(sa) == -1)
      if(errno == ENOENT) {
        sleep(1);
        continue;
      }
      else
        EC_FAIL snprintf(buf, sizeof(buf), "Hello from %ld!", (long)getpid());
    ec_neg1(write(fd_skt, buf, strlen(buf) + 1)) ec_neg1(read(fd_skt, buf, sizeof(buf)))
        printf("Client got \"%s\"\n", buf);
    ec_neg1(close(fd_skt)) exit(EXIT_SUCCESS);
  }
  return true;
  EC_CLEANUP_BGN
  /* only child gets here */
  exit(EXIT_FAILURE);
  EC_CLEANUP_END
}

int main(int argc, const char** argv) {

  ux::SockAddrUn sa{SOCKETNAME};

  return 0;
}