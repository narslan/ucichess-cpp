#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

namespace pgn2sqlite {

  class pgndb {
    const char* dbpath = "example.db3";

    public:
    pgndb();

    SQLiteCpp::Database mDb;
  };

} // namespace pgn2sqlite