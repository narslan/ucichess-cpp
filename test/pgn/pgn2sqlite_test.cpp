#include "../../src/ucichess/pgnread/pgnparse.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <stdexcept>

int main(int argc, const char** argv) {

  if(argc != 2) {
    throw std::runtime_error("supply a pgn file.");
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

  try {
    // Open a database file
    SQLite::Database db("example.db3");

    // Compile a SQL query, containing one parameter (index 1)
    SQLite::Statement query(db, "SELECT * FROM test WHERE size > ?");

    // Bind the integer value 6 to the first parameter of the SQL query
    query.bind(1, 6);

    // Loop to execute the query step by step, to get rows of result
    while(query.executeStep()) {
      // Demonstrate how to get some typed column value
      int id = query.getColumn(0);
      const char* value = query.getColumn(1);
      int size = query.getColumn(2);

      std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
    }
  }
  catch(std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}
