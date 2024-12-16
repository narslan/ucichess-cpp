#include "../../src/ucichess/pgn/parse.hpp"
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <stdexcept>

int main(int argc, const char** argv) {

  if(argc != 2) {
    throw std::runtime_error("supply a pgn file.");
  }

  std::string pgnFileArg = argv[1];
  std::filesystem::path pgnfile{pgnFileArg};
  if(pgnfile.extension() != ".pgn") {
    throw std::runtime_error("give a pgn file");
  }

  auto file_stream = std::ifstream(pgnfile);

  auto vis = std::make_unique<pgn2sqlite::Parser>(pgnfile.replace_extension());

  pgn::StreamParser parser(file_stream);
  parser.readGames(*vis);
}
