#include "../../src/ucichess/ux/process.hpp"
#include "../../src/ucichess/ux/socket.hpp"

const char* SOCKETNAME = "MySocket";

bool run_server(ux::SockAddrUn& sa) {

  int fd_hwm{}; //?

  ux::Socket fd_skt{-1};
  fd_skt.socket();
  fd_skt.bind(sa);
  fd_skt.listen(SOMAXCONN);

  if(fd_skt > fd_hwm)
    fd_hwm = fd_skt;
  //for select;
  fd_set set, read_set;
  FD_ZERO(&set);
  FD_SET(fd_skt, &set);

  while(true) {
    read_set = set;
    ux::File::select(fd_hwm + 1, &read_set, nullptr, nullptr, nullptr);
    for(int fdi = 0; fdi < fd_hwm; fdi++) {
      ux::File fd{fdi};
      if(FD_ISSET(fd, &read_set)) {
        if(fd == fd_skt) {
          auto fd_client = fd_skt.accept();
          FD_SET(fd_client, &set);
          if(fd_client > fd_hwm)
            fd_hwm = fd_client;
        }
      }
      else {
        char buf[100];
        int nread = fd.read(buf, sizeof(buf));
        if(nread == 0) {
          FD_CLR(fd, &set);
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
    ux::Socket fd_skt{-1};
    char buf[100];
    fd_skt.socket();
    fd_skt.connect(sa);

    if(errno == ENOENT) {
      sleep(1);
    }
    else {
      snprintf(buf, sizeof(buf), "Hello from %ld!", (long)getpid());
      fd_skt.write(buf, strlen(buf) + 1);
      fd_skt.read(buf, sizeof(buf));

      fmt::print("Client got \"{}\"\n", buf);
      fd_skt.close();
    }
    return true;
  }
  return false;
}

int main(int argc, const char** argv) {
  ::unlink(SOCKETNAME);
  ux::SockAddrUn sa{SOCKETNAME};
  int nclient;
  for(nclient = 1; nclient <= 4; nclient++) {
    run_client(sa);
  }
  run_server(sa);

  return 0;
}