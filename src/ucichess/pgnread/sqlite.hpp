#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
static const std::string dbpath = "example.db3";

class pgndb {
  public:
  pgndb()
      : mDb(dbpath, db("test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)){};
  SQLiteCpp::Database mDb;
}
