#include "../../src/ucichess/pgn/sqlite.hpp"

#include <fmt/core.h>

int main(int argc, const char** argv) {

  pgn2sqlite::pgndb p{"hello.db"};
  p.migrate();
}
