#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>
#include <ranges>

#include "../include/chess.hpp"

using namespace chess;

class MyVisitor : public pgn::Visitor {
   public:
    virtual ~MyVisitor() {}

    void startPgn() { board.setFen(constants::STARTPOS); }

    void header(std::string_view key, std::string_view value) {
  
    std::cout << key << " : "<< value << "\n";

    }
    
    void startMoves() {

    std::cout <<  "\n---------\n";
    }

    void move(std::string_view move, std::string_view comment) {
        
         using std::operator""sv;
 
         constexpr auto delim{" "sv};
         
         for (const auto word : std::views::split(move, delim)) {
           std::cout <<  std::string_view{word} << " "; 
             
         }
       
    }

    void endPgn() {
       std::string b =  board.getFen();
       
       
       
    }

   private:
    Board board;
};

int main(int argc, char const *argv[]) {
    const auto file  = "../../lichess_db_standard_rated_2017-03.pgn";
    auto file_stream = std::ifstream(file);

    auto vis = std::make_unique<MyVisitor>();

    const auto t0 = std::chrono::high_resolution_clock::now();

    pgn::StreamParser parser(file_stream);
    parser.readGames(*vis);

    const auto t1 = std::chrono::high_resolution_clock::now();

    const auto file_size_mb = std::filesystem::file_size(file) / 1000.0 / 1000.0;

    std::cout << "MB/s: "
              << (file_size_mb / (std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() / 1000.0))
              << "\n";

    std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() / 1000.0) << "\n";

    return 0;
}
