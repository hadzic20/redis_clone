#include <iostream>
#include <vector>

#include "redis.hpp"

using namespace std;

void repl() {
  Store store;
  while (1) {
    string line;
    cout << "\033[1;32m> \033[1;0m";
    getline(cin, line);
    vector<string> args = parse(line);
    string tmp = CommandHandler::command_handler(&store, args);
    if (tmp == "quit") {
      break;
    }
    if (tmp == "blank line") {
      continue;
    }
    cout << tmp << endl;
  }
}

int main() { repl(); }
