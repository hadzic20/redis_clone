#pragma once

using namespace std;

class Hash {
  map<string, string> my_hash;

 public:
  string set(vector<string> args) {
    if (args.size() < 3) {
      args.push_back("");
    }
    if (!my_hash.insert(pair<string, string>(args[1], args[2])).second) {
      my_hash.find(args[1])->second = args[2];
    }
    return ("OK");
  }
  string get(vector<string> args) {
    if (args.size() < 2) {
      string rtrn = "(error) wrong number of arguments (given ";
      rtrn += (args.size() - 1 + '0');
      rtrn += ", expected 1)";
      return (rtrn);
    }
    auto itr = my_hash.find(args[1]);
    if (itr != my_hash.end()) {
      return ("\"" + itr->second + "\"");
    }
    return ("(nil)");
  }

  string del(vector<string> args) {
    if (args.size() < 2) {
      string rtrn = "(error) wrong number of arguments (given ";
      rtrn += (args.size() - 1 + '0');
      rtrn += ", expected 1)";
      return (rtrn);
    }
    if (my_hash.find(args[1]) != my_hash.end()) {
      my_hash.erase(args[1]);
      return ("(integer) 1");
    }
    return ("(nil)");
  }
};
