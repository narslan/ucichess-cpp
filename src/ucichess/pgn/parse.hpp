#pragma once

#include <fmt/core.h>
#include <memory>
#include <string>
#include <string_view>

#include "../chess/chess.hpp"
#include "ucichess/pgn/sqlite.hpp"

using namespace chess;
namespace pgn2sqlite {
  class Parser : public pgn::Visitor {
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
    std::vector<std::pair<std::string_view, std::string_view>> headers;
    std::vector<std::string_view> moves;
  };
} // namespace pgn2sqlite