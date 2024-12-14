#include "../../src/ucichess/pgn/sqlite.hpp"

#include <fmt/core.h>
#include <stdexcept>

int main(int argc, const char** argv) {

  if(argc != 2) {
    throw std::runtime_error("supply a pgn file.");
  }

  std::string file = argv[1];

  pgn2sqlite::pgndb();
}
