#include "parse.hpp"
#include <algorithm>
#include <fmt/format.h>
#include <string_view>
#include <utility>

namespace pgn2sqlite {

  /*! note: delimiter cannot contain NUL characters
 */
  template <typename Range, typename Value = typename Range::value_type>
  std::string Join(Range const& elements, const char* const delimiter) {
    std::ostringstream os;
    auto b = begin(elements), e = end(elements);

    if(b != e) {
      std::copy(b, prev(e), std::ostream_iterator<Value>(os, delimiter));
      b = prev(e);
    }
    if(b != e) {
      os << *b;
    }

    return os.str();
  }

  /*! note: imput is assumed to not contain NUL characters
 */
  template <typename Input, typename Output, typename Value = typename Output::value_type>
  void Split(char delimiter, Output& output, Input const& input) {
    using namespace std;
    for(auto cur = begin(input), beg = cur;; ++cur) {
      if(cur == end(input) || *cur == delimiter || !*cur) {
        output.insert(output.end(), Value(beg, cur));
        if(cur == end(input) || !*cur)
          break;
        else
          beg = next(cur);
      }
    }
  }

  Parser::Parser()
      : db{std::make_unique<pgn2sqlite::pgndb>("abdo.db")} {
    db->migrate();
  };

  void Parser::startPgn() {
    board.setFen(constants::STARTPOS);

    fmt::print("Start pgn:\n");
  }

  void Parser::header(std::string_view key, std::string_view value) {

    headers.push_back(std::make_pair(key, value));
  }

  void Parser::startMoves() {

    fmt::print("Start Moves:\n");
    //
  }

  void Parser::move(std::string_view move, std::string_view comment) {

    auto m = uci::parseSan(board, move);
    board.makeMove(m);
    moves.push_back(move);
  }

  void Parser::endPgn() {
    std::string b = board.getFen();
    m_counter.increment_if_not_zero();

    std::string event, site, date, eco, player1, player2, result;
    std::string moves_string = Join(moves, " ");
    fmt::print("End pgn start\n");

    for(auto el : headers) {
      fmt::print("+++++'{}' '{}'\n", el.first, el.second);
    }
    auto it = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "Event";
        });
    event = it->second;

    auto it2 = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "Site";
        });
    site = it2->second;

    auto it3 = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "Date";
        });
    date = it3->second;
    auto it4 = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "Eco";
        });
    eco = it4->second;
    auto it5 = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "White";
        });
    player1 = it5->second;
    auto it6 = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "Black";
        });
    player2 = it6->second;
    auto it7 = std::find_if(
        headers.begin(), headers.end(), [&](std::pair<std::string_view, std::string_view> p) {
          return p.first == "Result";
        });
    result = it7->second;

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
    try {
      db->db.exec(query);

      SQLite::Statement query2(db->db, "SELECT * FROM pgn");

      while(query2.executeStep()) {
        fmt::print("{} {} \n", query2.getColumn(1).getInt(), query2.getColumn(2).getInt());
      }
      headers.clear();
      moves.clear();
    }
    catch(const std::exception& e) {
      fmt::print("SQLite Error {}\n", e.what());
    }

    fmt::print("number of pgn  files: {} \n", m_counter.read() - 1);
  }

} // namespace pgn2sqlite