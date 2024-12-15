#pragma once

#include <fmt/core.h>
#include <memory>

#include <string_view>

#include "../chess/chess.hpp"

#include "ucichess/pgn/sqlite.hpp"

using namespace chess;
namespace pgn2sqlite {

  using Texts = std::vector<std::string>;

  class Parser : public pgn::Visitor {

    struct Counter {
      bool increment_if_not_zero() {
        if(counter > 0) {
          counter++;
          return true;
        }
        return false;
      };
      bool decrement() {
        return (--counter == 0);
      };

      uint64_t read() {
        return counter;
      };
      uint64_t counter{1};
    };

    // struct PGNRow {
    //   std::vector<std::pair<std::string_view, std::string_view>> m_headers;
    //   std::vector<std::string_view> m_moves;
    // };

    public:
    virtual ~Parser() { }
    Parser();
    void startPgn();

    void header(std::string_view key, std::string_view value);

    void startMoves();
    void move(std::string_view move, std::string_view comment);

    void endPgn();

    private:
    Board board;
    std::unique_ptr<pgn2sqlite::pgndb> db;
    Counter m_counter;
  };
} // namespace pgn2sqlite