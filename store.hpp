#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Store {
  map<string, string> my_hash;
  map<string, list<string>> my_lists;

 public:
  string set(string key, string value) {
    if (my_lists.find(key) != my_lists.end()) {
      my_lists.erase(key);
    }
    if (!my_hash.insert(pair<string, string>(key, value)).second) {
      my_hash.find(key)->second = value;
    }
    return ("+OK\r\n");
  }

  string get(string key) {
    auto itr = my_hash.find(key);
    if (itr != my_hash.end()) {
      return ("$\"" + itr->second + "\"\r\n");
    }
    return ("$(nil)\r\n");
  }

  string del(string key) {
    if (my_hash.find(key) != my_hash.end()) {
      my_hash.erase(key);
      return (":1\r\n");
    }
    if (my_lists.find(key) != my_lists.end()) {
      my_lists.erase(key);
      return (":1\r\n");
    }
    return ("$(nil)\r\n");
  }

  string lindex(string list_name, int key) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty() ||
        (size_t)key >= itr->second.size()) {
      return ("$(nil)\r\n");
    }
    auto list_itr = itr->second.begin();
    int i = 0;
    while (++i <= key) {
      list_itr++;
    }
    return (*list_itr);
  }

  string lset(string list_name, int key, string value) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end()) {
      return ("-ERR no such key\r\n");
    }
    if (itr->second.empty() || (size_t)key >= itr->second.size()) {
      return ("-ERR index out of range\r\n");
    }
    auto list_itr = itr->second.begin();
    int i = 0;
    while (++i <= key) {
      list_itr++;
    }
    *list_itr = value;
    return ("+OK\r\n");
  }

  string llen(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end()) {
      return (":0\r\n");
    }
    string rtrn = ":";
    rtrn += (itr->second.size() + '0');
    rtrn += "\r\n";
    return (rtrn);
  }

  string lpush(const vector<string>& args) {
    if (my_hash.find(args[1]) != my_hash.end()) {
      return (
          "-WRONGTYPE Operation against a key holding the wrong kind of value\r\n");
    }
    auto itr = my_lists.find(args[1]);

    if (itr == my_lists.end()) {
      list<string> new_list;
      size_t i = 1;
      while (++i < args.size()) {
        new_list.push_front(args[i]);
      }
      my_lists.insert(pair<string, list<string>>(args[1], new_list));
      string rtrn = ":";
      rtrn += (new_list.size() + '0');
      rtrn += "\r\n";
      return (rtrn);
    }

    size_t i = 1;
    while (++i < args.size()) {
      itr->second.push_front(args[i]);
    }
    string rtrn = ":";
    rtrn += (itr->second.size() + '0');
    rtrn += "\r\n";
    return (rtrn);
  }

  string lpop(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return ("$(nil)\r\n");
    }
    string rtrn = "$";
    rtrn += itr->second.front();
    rtrn += "\r\n";
    itr->second.pop_front();
    return (rtrn);
  }

  string rpush(const vector<string>& args) {
    if (my_hash.find(args[1]) != my_hash.end()) {
      return (
          "-WRONGTYPE Operation against a key holding the wrong kind of value\r\n");
    }
    auto itr = my_lists.find(args[1]);
    if (itr == my_lists.end()) {
      list<string> new_list;
      size_t i = 1;
      while (++i < args.size()) {
        new_list.push_back(args[i]);
      }
      my_lists.insert(pair<string, list<string>>(args[1], new_list));
      string rtrn = ":";
      rtrn += (new_list.size() + '0');
      rtrn += "\r\n";
      return (rtrn);
    }
    size_t i = 1;
    while (++i < args.size()) {
      itr->second.push_back(args[i]);
    }
    string rtrn = ":";
    rtrn += (itr->second.size() + '0');
    rtrn += "\r\n";
    return (rtrn);
  }

  string rpop(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return ("$(nil)\r\n");
    }
    string rtrn = "$";
    rtrn += itr->second.back();
    rtrn += "\r\n";
    itr->second.pop_back();
    return (rtrn);
  }

  string lrange(string list_name, int start, int end) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return ("$(empty list or set)\r\n");
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
      rtrn += lindex(list_name, index++);
      rtrn += "\r\n";
    }
    return (rtrn);
  }
};