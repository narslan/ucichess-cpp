#include "../../src/ucichess/uci/command.hpp"
#include "../../src/ucichess/uci/process.hpp"
#include <iostream>
#include <sstream>
#include <vector>

// split_s is the core machinery. It split s at splitPoint, and returns a vector.
std::vector<std::string> split_s(const std::string& s, char delimeter)
{
  std::vector<std::string> elements;
  std::stringstream string_stream(s);
  std::string item;
  while(std::getline(string_stream, item, delimeter)) {
    elements.push_back(item);
  }
  return elements;
}

int main(int argc, const char** argv)
{
  ucichess::ChessEngine c{"stockfish"};
  std::map<std::string, std::string> options;
  c.initEngine(10, options);

  std::string in;
  bool quit_flag = false;

  while(!quit_flag && std::getline(std::cin, in)) {

    auto args = split_s(in, ' ');

    std::string command = args[0];
    bool command_found = false;
    for(ucichess::command uci_command : ucichess::uci_commands) {

      if(command == uci_command.name) {
        command_found = true;
        uci_command.func(c, args);
        if(command == "quit") {
          c.quit();
          quit_flag = true;
        }
        else {
          continue;
        }
      }
    }
    if(!command_found) {
      std::cout << "Received unknown command: " << command;
    }
  }

  return 0;
}