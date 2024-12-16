#include "parse.hpp"
#include <fmt/format.h>
#include <future>
#include <memory>
#include <string>
#include <string_view>

namespace pgn2sqlite {

  /*! note: delimiter cannot contain NUL characters
 */

  Parser::Parser()
      : db{std::make_unique<pgn2sqlite::pgndb>("abdo.db")} {
    db->migrate();
  };

  void Parser::startPgn() {
    board.setFen(constants::STARTPOS);
    moves_.clear();
    comments_.clear();
    count_ = 0;
    game_count_++;
    //fmt::print("Start pgn: counter {}\n", m_counter.read());
  }

  std::string returnTwo() {
    return "hello";
  }

  void Parser::header(std::string_view key, std::string_view value) {
    //fmt::print("header: counter {}\n", m_counter.read());
    //fmt::print("{} {}\n", key, value);

    std::future<std::string> f = std::async(std::launch::async, returnTwo);
  }

  void Parser::startMoves() {
    move_start_count_++;
    assert(end_count_ == game_count_ - 1);
  }

  void Parser::move(std::string_view move, std::string_view comment) {
    fmt::print("move counter {}\n", m_counter.read());

    count_++;

    if(comment.size() > 0) {
      comments_.push_back(std::string(comment));
    }

    moves_.push_back(std::string(move));

    auto m = uci::parseSan(board, move);
    // fmt::print("{}\n", move m_moves.push_back(move);
    board.makeMove(m);
  }

  void Parser::endPgn() {
    //std::string b = board.getFen();
    m_counter.increment_if_not_zero();

    std::string event, site, date, eco, player1, player2, result, moves_string;
    //std::string moves_string = Join(moves, " ");
    fmt::print("-------------\nEnd pgn:\n");

    // for(auto el : headers) {
    //   fmt::print("'{}':'{}'\n", el.first, el.second);
    // }

    // auto it = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "Event";
    //     });
    // event = it->second;

    // auto it2 = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "Site";
    //     });
    // site = it2->second;

    // auto it3 = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "Date";
    //     });
    // date = it3->second;
    // auto it4 = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "Eco";
    //     });
    // eco = it4->second;
    // auto it5 = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "White";
    //     });
    // player1 = it5->second;
    // auto it6 = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "Black";
    //     });
    // player2 = it6->second;
    // auto it7 = std::find_if(
    //     headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
    //       return p.first == "Result";
    //     });
    // result = it7->second;

    auto query = fmt::format("insert into pgn values (NULL, {}, {}, {}, {}, {}, {}, {}, {} ) ",
                             event,
                             site,
                             date,
                             eco,
                             player1,
                             player2,
                             result,
                             moves_string);
    fmt::print("{}\n", query);
    fmt::print("last: {}\n", m_counter.read());
    // headers.clear();
    // moves.clear();

    // try {
    //   db->db.exec(query);

    //   SQLite::Statement query2(db->db, "SELECT * FROM pgn");

    //   while(query2.executeStep()) {
    //     fmt::print("{} {} \n", query2.getColumn(1).getInt(), query2.getColumn(2).getText());
    //   }
    //   headers.clear();
    //   moves.clear();
    // }
    // catch(const std::exception& e) {
    //   fmt::print("SQLite Error {}\n", e.what());
    // }
  }

} // namespace pgn2sqlite