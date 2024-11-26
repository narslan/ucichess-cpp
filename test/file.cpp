#include "../src/process/file.hpp"
#include "../src/error/error.hpp"
#include "../src/process/process.hpp"

using f = chessbird::File;
using p = chessbird::Process;
void pipeRead() {

  f pfd[2];
  f::pipe(pfd);
  char s[100];
  EC_CATCH(pfd[1].write("helloxx", 8));
  auto nread = pfd[0].read(s, sizeof(s));
  if(nread == 0)
    printf("EOF\n");
  else
    printf("read %ld bytes: %s\n", (long)nread, s);
}

void read(chessbird::File pfd) {
  fmt::print("we are in read");
  char s[10000];
  auto nread = pfd.read(s, sizeof(s));
  if(nread == 0) {
    printf("EOF\n");
  }
  else {
    printf("read %ld bytes: %s\n", (long)nread, s);
  }
}

void pipeWrite() {

  f pfd[2];
  EC_CATCH(f::pipe(pfd));

  constexpr size_t nbytes = 4;
  p pid = p::fork();
  switch(pid) {
  case -1:
    chessbird::Error(errno, EC_RESOURCE);
  case 0: // child.

    pfd[0].dup2(STDIN_FILENO);
    pfd[0].close();
    pfd[1].close();
    read(STDIN_FILENO);
    EC_CATCH(p::execlp("stockfish"));

  default: // parent.
    pfd[0].close();
    pfd[1].write("uci\n", nbytes);
    pfd[1].write("quit\n", 5);
    p::wait(pid);
  }
}

int main(int argc, const char** argv) {
  pipeWrite();
  return 0;
}