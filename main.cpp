#include <iostream>
#include <vector>

#include "redis.hpp"

using namespace std;

void repl() {
  Store store;
  while (1) {
    string line;
    cout << "> ";
    getline(cin, line);
    vector<string> args = parse(line);
    string tmp = CommandHandler::function_mapper(&store, args);
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
