#include "../../src/ucichess/pgnread/pgnparse.hpp"
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <stdexcept>

int main(int argc, const char** argv) {

  if(argc != 2) {
    throw std::runtime_error("supply a pgn file...rrrr");
  }

  std::string file = argv[1];

  auto file_stream = std::ifstream(file);

  auto vis = std::make_unique<MyVisitor>();

  const auto t0 = std::chrono::high_resolution_clock::now();

  pgn::StreamParser parser(file_stream);
  parser.readGames(*vis);

  const auto t1 = std::chrono::high_resolution_clock::now();

  const auto file_size_mb = std::filesystem::file_size(file) / 1000.0 / 1000.0;
  fmt::print("{}\n",
             file_size_mb /
                 (std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() / 1000.0));
  fmt::print("{}\n",
             std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() / 1000.0);
}
