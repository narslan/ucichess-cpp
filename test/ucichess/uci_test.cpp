#include "../../src/ucichess/uci/command.hpp"
#include "../../src/ucichess/uci/engine.hpp"

#include <algorithm>
#include <fmt/core.h>
#include <sstream>
#include <vector>

// split_s is the core machinery. It split s at splitPoint, and returns a vector.
std::vector<std::string> split_s(const std::string& s, char delimeter) {
  std::vector<std::string> elements;
  std::stringstream string_stream(s);
  std::string item;
  while(std::getline(string_stream, item, delimeter)) {
    elements.push_back(item);
  }
  return elements;
}

struct FindByName {
  const std::string name;
  FindByName(const char* name)
      : name(name) { }
  bool operator()(const ucichess::command& j) const {
    return j.name == name;
  }
};

int main(int argc, const char** argv) {
  ucichess::ChessEngine c{"stockfish"};

  c.initEngine();

  std::string in;

  while(std::getline(std::cin, in)) {

    auto args = split_s(in, ' ');

    std::string command = args[0];

    if(command == "quit") {
      std::vector<ucichess::command>::iterator it = std::find_if(
          ucichess::uci_commands.begin(), ucichess::uci_commands.end(), FindByName("quit"));
      if(it != ucichess::uci_commands.end()) {
        it->func(c, {});
      }
      break;
    }
    bool command_found = false;
    for(auto uci_command : ucichess::uci_commands) {

      if(command == uci_command.name) {
        command_found = true;
        fmt::print("uci_command: '{}'\n", uci_command.name);
        uci_command.func(c, {});
        continue;
      }
    }
    if(!command_found) {
      fmt::print("command not_found '{}'\n", command);
    }
  }

  return 0;
}