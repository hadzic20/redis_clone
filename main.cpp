#include "redis.hpp"

using namespace std;

void repl() {
  Hash hash;
  while (1) {
    string line;
    cout << "> ";
    getline(cin, line);
    vector<string> args = parse(line);
    string tmp = function_mapper(&hash, args);
    if (tmp == "quit") {
      break;
    } else if (tmp == "blank line") {
      continue;
    } else {
      cout << tmp << endl;
    }
  }
}

int main() { repl(); }
