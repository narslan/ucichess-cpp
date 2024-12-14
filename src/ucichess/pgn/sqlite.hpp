#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

namespace pgn2sqlite {

  class pgndb {

    public:
    pgndb(std::string dbpath);
    ~pgndb() = default;
    void migrate();

    SQLite::Database db;
  };

} // namespace pgn2sqlite