#pragma once
#include <iostream>
#include <map>

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
    }
    return ("(nil)");
  }

  string del(string key) {
    if (my_hash.find(key) != my_hash.end()) {
      my_hash.erase(key);
      return ("(integer) 1");
    }
    return ("(nil)");
  }
};
