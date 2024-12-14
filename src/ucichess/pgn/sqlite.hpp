#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

namespace pgn2sqlite {

  class pgndb {
    const char* dbpath = "example.db3";

    public:
    pgndb();
    ~pgndb() {
      remove(dbpath);
    };
    void migrate();

    SQLite::Database db;
  };

} // namespace pgn2sqlite