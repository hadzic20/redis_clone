#include "redis.hpp"
#include <iostream>
#include <vector>

using namespace std;

void repl() {
  Hash hash;
  List list;
  while (1) {
    string line;
    cout << "> ";
    getline(cin, line);
    vector<string> args = parse(line);
    string tmp = function_mapper(&list, &hash, args);
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
