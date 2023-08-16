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
    string rtrn = "\033[1;";
    if (tmp[0] == '+') {
        rtrn += "32m";
    }
    if (tmp[0] == '-') {
        rtrn += "31m";
    }
    if (tmp[0] == ':') {
        rtrn += "33m";
    }
    if (tmp[0] == '$') {
      rtrn += "35m";
    }
    rtrn += tmp.substr(1, tmp.size());
    rtrn += "\033[1;0m";
    cout << rtrn << endl;
  }
}

int main() { repl(); }
