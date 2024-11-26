#include "../process/process.hpp"

#include <fmt/core.h>
#include <sys/types.h>
using namespace chessbird;
using namespace fmt;

// void forktest() {
//   int pid;
//   print("Start of test\n");
//   pid = Process::fork();

//   if(pid == 0) {
//     print(" I'm the child with pid {}\n", Process::getpid());
//   }
//   else {
//     print("I'm in parent, the child has {} \n", pid);
//   }
//   print("End of test\n");
// }

// void executetest() {

//   print("Start of executetest\n");
//   //We store thie information of childs here.

//   Process::execute("date");
//   //fmt::print("cid: {}\n", *(cid.get()));
//   pid_t id = Process::getpid();
//   fmt::print("[executetest] pid: {}\n", id);
//   print("End of executetest\n");
// }

// void executeStockfishTest() {

//   print("Start of executeStockfishTest\n");
//   //We store thie information of childs here.

//   Process::execute("stockfish");
//   //fmt::print("cid: {}\n", *(cid.get()));
//   pid_t id = Process::getpid();
//   fmt::print("[executeStockfishTest] pid: {}\n", id);
//   print("End of executeStockfishTest\n");
// }

// void resourceTest() {
//   fmt::print("before getpid:\n");
//   long mem = Resource::memusage();
//   fmt::print("memory:{} KB \n", mem);

//   Process::execute("ps", "ax");
// }

// void execvpeTest() {

//   print("Start of execvpeTest\n");

//   char* ev[] = {nullptr};

//   Process::execute2("ps", ev, "ax");
//   //fmt::print("cid: {}\n", *(cid.get()));
//   pid_t id = Process::getpid();
//   fmt::print("[execvpeTest] pid: {}\n", id);
//   print("End of execvpeTest\n");
// }

// void execvpeTest() {

//   print("Start of execvpeTest\n");

//   char* ev[] = {nullptr};

//   Process::execute("ps", ev, "ax");
//   //fmt::print("cid: {}\n", *(cid.get()));
//   pid_t id = Process::getpid();
//   fmt::print("[execvpeTest] pid: {}\n", id);
//   print("End of execvpeTest\n");
// }

void execlpTest() {

  print("Start of execlpTest\n");

  //Process::execute("ps", nullptr, "ps", "ax");

  Process::execute2("stockfish");
  //fmt::print("cid: {}\n", *(cid.get()));

  print("End of execlpTest\n");
}

int main(int argc, const char** argv) {

  // fmt::print("{} {} \n", Process::getpid(), Process::getuid());
  //Process::execlp("/usr/bin/echo", "asdad", "dsd");

  //  Process::execvp("stockfish");
  //forktest();
  //executetest();
  //executetest();
  execlpTest();

  return 0;
}