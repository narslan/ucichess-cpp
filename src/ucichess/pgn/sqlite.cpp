#include "ucichess/pgn/sqlite.hpp"
#include <fmt/core.h>
namespace pgn2sqlite {

  pgndb::pgndb(std::string path)
      : db{SQLite::Database(path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)} {
    fmt::print("{} opened successfully", db.getFilename());
  };
  void pgndb::migrate() {
    // Create a new table with an explicit "id" column aliasing the underlying rowid
    db.exec("DROP TABLE IF EXISTS pgn");
    db.exec(R"(
        create table pgn ( 
        pgn_id integer primary key,
        event text,
        site text,
        date text,
        round text,
        white text,
        black text,
        result text,
        moves text);
        )");
  };

} // namespace pgn2sqlite

// std::make_unique<pgn2sqlite::pgndb>("abdo.db");