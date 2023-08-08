#include <cstring>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class Hash {
  map<string, string> my_hash;

 public:
  string set(string key, string value) {
    if (!my_hash.insert(pair<string, string>(key, value)).second) {
      my_hash.find(key)->second = value;
    }
    return ("OK");
  }
  string get(string key) {
    auto itr = my_hash.find(key);
    if (itr != my_hash.end()) {
      return ("\"" + itr->second + "\"");
    } else {
      return ("(nil)");
    }
  }

  string del(string key) {
    if (my_hash.find(key) != my_hash.end()) {
      my_hash.erase(key);
      return ("(integer) 1");
    } else {
      return ("(nil)");
    }
  }
};

string* parse(string line) {
  int iterator = 0;
  int index = 0;
  string* args = new string[line.length()];
  if (line == "") {
    return (NULL);
  }
  while (line[iterator] != '\0') {
    while (line[iterator] == ' ' || line[iterator] == '\t') {
      iterator++;
    }
    if (line[iterator] == '"') {
      iterator++;
      while (line[iterator] != '"') {
        args[index] += line[iterator++];
      }
      iterator++;
      index++;
      continue;
    }
    while (line[iterator] != ' ' && line[iterator] != '\t' && line[iterator] != '\0') {
      args[index] += line[iterator++];
    }
    index++;
  }
  return (args);
}

string function_mapper(Hash* hash, string* args) {
  if (!args[0].compare("q"))
    return ("quit");
  else if (!args[0].compare(""))
    return ("blank line");
  else {
    if (!args[0].compare("set")) {
      return (hash->set(args[1], args[2]));
    } else if (!args[0].compare("get")) {
      return (hash->get(args[1]));
    } else if (!args[0].compare("del")) {
      return (hash->del(args[1]));
    } else {
      return ("(error) I'm sorry, I don't recognize that command");
    }
  }
}

void repl() {
  Hash hash;
  while (1) {
    string line;
    cout << "> ";
    getline(cin, line);
    string* args = parse(line);
    string tmp = function_mapper(&hash, args);
    delete[] args;
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