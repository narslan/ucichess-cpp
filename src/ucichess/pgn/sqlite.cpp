#include "ucichess/pgn/sqlite.hpp"
#include <fmt/core.h>
namespace pgn2sqlite {

  pgndb::pgndb()
      : db{SQLite::Database("test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)} {
    fmt::print("{} opened successfully", db.getFilename());
  };
  void pgndb::migrate() {
    // Create a new table with an explicit "id" column aliasing the underlying rowid
    db.exec("DROP TABLE IF EXISTS test");
    db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

    // first row
    int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
    fmt::print("{} returned \n", nb);

    // second row
    nb = db.exec("INSERT INTO test VALUES (NULL, \"second\")");
    fmt::print("{} returned \n", nb);

    // update the second row
    nb = db.exec("UPDATE test SET value=\"second-updated\" WHERE id='2'");
    fmt::print("{} returned \n", nb);

    // Check the results : expect two row of result
    SQLite::Statement query(db, "SELECT * FROM test");

    while(query.executeStep()) {

      fmt::print("{} {}\n", query.getColumn(0).getInt(), query.getColumn(1).getText());
    }

    db.exec("DROP TABLE test");
  };

} // namespace pgn2sqlite