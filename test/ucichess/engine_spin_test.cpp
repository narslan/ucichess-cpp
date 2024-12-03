#include "../../src/ucichess/uci/process.hpp"
#include "nonstd/expected.hpp"
using namespace nonstd;
using namespace std::literals;

auto spin_engine(char const* const text) -> expected<int, std::string>
{
  ucichess::ChessEngine e{"stockfish"};

  std::map<std::string, std::string> options;

  e.initEngine(10, options);

  if(pos != text)
    return value;
  else
    return make_unexpected("'"s + text + "' isn't a number");
}

int main() { }