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

    public:
    virtual ~Parser() { }
    Parser();
    void startPgn();

    void header(std::string_view key, std::string_view value);

    void startMoves();
    void move(std::string_view move, std::string_view comment);

    void endPgn();

    int count() const {
      return count_;
    }
    int gameCount() const {
      return game_count_;
    }
    int endCount() const {
      return end_count_;
    }
    int moveStartCount() const {
      return move_start_count_;
    }
    const auto& comments() const {
      return comments_;
    }
    const auto& moves() const {
      return moves_;
    }
    const auto& headers() const {
      return headers_;
    }

    private:
    Board board;
    std::unique_ptr<pgn2sqlite::pgndb> db;
    Counter m_counter;

    std::vector<std::string> comments_;
    std::vector<std::string> moves_;
    std::vector<std::string> headers_;

    int end_count_ = 0;
    int game_count_ = 0;
    int count_ = 0;
    int move_start_count_ = 0;
  };
} // namespace pgn2sqlite