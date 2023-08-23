#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>

#include "return_value.hpp"

using namespace std;

class Store {
  map<string, string> my_hash;
  map<string, list<string>> my_lists;

 public:
  ReturnValue* set(string key, string value) {
    if (my_lists.find(key) != my_lists.end()) {
      my_lists.erase(key);
    }
    if (!my_hash.insert(pair<string, string>(key, value)).second) {
      my_hash.find(key)->second = value;
    }
    return new MyString("OK");
  }

  ReturnValue* get(string key) {
    auto itr = my_hash.find(key);
    if (itr != my_hash.end()) {
      return new BulkString("\"" + itr->second + "\"");
    }
    return new BulkString("(nil)");
  }

  ReturnValue* del(string key) {
    if (my_hash.find(key) != my_hash.end()) {
      my_hash.erase(key);
      return new Integer("1");
    }
    if (my_lists.find(key) != my_lists.end()) {
      my_lists.erase(key);
      return new Integer("1");
    }
    return new BulkString("(nil)");
  }

  ReturnValue* lindex(string list_name, int key) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty() ||
        (size_t)key >= itr->second.size()) {
      return new BulkString("(nil)");
    }
    auto list_itr = itr->second.begin();
    int i = 0;
    while (++i <= key) {
      list_itr++;
    }
    return new MyString(*list_itr);
  }

  ReturnValue* lset(string list_name, int key, string value) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end()) {
      return new Error("ERR no such key");
    }
    if (itr->second.empty() || (size_t)key >= itr->second.size()) {
      return new Error("ERR index out of range");
    }
    auto list_itr = itr->second.begin();
    int i = 0;
    while (++i <= key) {
      list_itr++;
    }
    *list_itr = value;
    return new MyString("OK");
  }

  ReturnValue* llen(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end()) {
      return new Integer("0");
    }
    string rtrn = "";
    rtrn += (itr->second.size() + '0');
    return new Integer(rtrn);
  }

  ReturnValue* lpush(const vector<string>& args) {
    if (my_hash.find(args[1]) != my_hash.end()) {
      return new Error(
          "WRONGTYPE Operation against a key holding the wrong kind of value");
    }
    auto itr = my_lists.find(args[1]);

    if (itr == my_lists.end()) {
      list<string> new_list;
      size_t i = 1;
      while (++i < args.size()) {
        new_list.push_front(args[i]);
      }
      my_lists.insert(pair<string, list<string>>(args[1], new_list));
      string rtrn = "";
      rtrn += (new_list.size() + '0');
      return new Integer(rtrn);
    }

    size_t i = 1;
    while (++i < args.size()) {
      itr->second.push_front(args[i]);
    }
    string rtrn = "";
    rtrn += (itr->second.size() + '0');
    return new Integer(rtrn);
  }

  ReturnValue* lpop(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return new BulkString("(nil)");
    }
    string rtrn = "";
    rtrn += itr->second.front();
    itr->second.pop_front();
    return new BulkString(rtrn);
  }

  ReturnValue* rpush(const vector<string>& args) {
    if (my_hash.find(args[1]) != my_hash.end()) {
      return new Error(
          "WRONGTYPE Operation against a key holding the wrong kind of value");
    }
    auto itr = my_lists.find(args[1]);
    if (itr == my_lists.end()) {
      list<string> new_list;
      size_t i = 1;
      while (++i < args.size()) {
        new_list.push_back(args[i]);
      }
      my_lists.insert(pair<string, list<string>>(args[1], new_list));
      string rtrn = "";
      rtrn += (new_list.size() + '0');
      return new Integer(rtrn);
    }
    size_t i = 1;
    while (++i < args.size()) {
      itr->second.push_back(args[i]);
    }
    string rtrn = "";
    rtrn += (itr->second.size() + '0');
    return new Integer(rtrn);
  }

  ReturnValue* rpop(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return new BulkString("(nil)");
    }
    string rtrn = "";
    rtrn += itr->second.back();
    itr->second.pop_back();
    return new BulkString(rtrn);
  }

  ReturnValue* lrange(string list_name, int start, int end) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return new BulkString("(empty list or set)");
    }
    size_t nbr = 0;
    int index = start;
    string rtrn;
    if (end < 0) {
      end = itr->second.size() + end;
    }
    while (++nbr <= itr->second.size() && index <= end) {
      rtrn += (nbr + '0');
      rtrn += ") ";
      rtrn += lindex(list_name, index++)->getMessage();
      rtrn += "\r\n";
    }
    return new Array(rtrn);
  }
};