#include "../process/process.hpp"

#include <sys/types.h>
using namespace ucichess;

void execlpTest() {

  Process::execute2("stockfish");
}

int main(int argc, const char** argv) {

  execlpTest();

  return 0;
}