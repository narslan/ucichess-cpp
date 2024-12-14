#pragma once

#include "ucichess/pgn/sqlite.hpp"
namespace pgn2sqlite {

  pgndb::pgndb()
      : mDb(dbpath, db("test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)){};
}