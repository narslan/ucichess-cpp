#include "../../src/ucichess/pgn/parse.hpp"
#include <fmt/core.h>
#include <fstream>
#include <stdexcept>

int main(int argc, const char** argv) {

  if(argc != 2) {
    throw std::runtime_error("supply a pgn file.");
  }

  std::string file = argv[1];

  auto file_stream = std::ifstream(file);

  auto vis = std::make_unique<pgn2sqlite::Parser>();

  pgn::StreamParser parser(file_stream);
  parser.readGames(*vis);

  for(auto el : vis->moves()) {
    fmt::print("{}\n", el);
  }
}
