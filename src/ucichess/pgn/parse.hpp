#pragma once

#include <fmt/core.h>
#include <string_view>

#include "../chess/chess.hpp"

using namespace chess;
namespace pgn2sqlite {
  class Parser : public pgn::Visitor {
    public:
    virtual ~Parser() { }

    void startPgn();

    void header(std::string_view key, std::string_view value);

    void startMoves();
    void move(std::string_view move, std::string_view comment);

    void endPgn();

    private:
    Board board;
  };
} // namespace pgn2sqlite