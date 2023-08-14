#pragma once
#include <list>
#include <map>

using namespace std;

class List {
  map<string, list<string>> my_lists;

 public:
  string lindex(string list_name, int key) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty() ||
        (size_t)key >= itr->second.size()) {
      return ("(nil)");
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
      return ("(error) ERR no such key");
    }
    if (itr->second.empty() || (size_t)key >= itr->second.size()) {
      return ("(error) ERR index out of range");
    }
    auto list_itr = itr->second.begin();
    int i = 0;
    while (++i <= key) {
      list_itr++;
    }
    *list_itr = value;
    return ("OK");
  }

  string llen(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end()) {
      return ("(integer) 0");
    }
    string rtrn = "(integer) ";
    rtrn += (itr->second.size() + '0');
    return (rtrn);
  }

  string lpush(vector<string>& args) {
    auto itr = my_lists.find(args[1]);
    
    if (itr == my_lists.end()) {
      list<string> new_list;
      size_t i = 1;
      while (++i < args.size()) {
        new_list.push_front(args[i]);
      }
      my_lists.insert(pair<string, list<string>>(args[1], new_list));
      string rtrn = "(integer) ";
      rtrn += (new_list.size() + '0');
      return (rtrn);
    }

    size_t i = 1;
    while (++i < args.size()) {
      itr->second.push_front(args[i]);
    }
    string rtrn = "(integer) ";
    rtrn += (itr->second.size() + '0');
    return (rtrn);
  }

  string lpop(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return ("(nil)");
    }
    string rtrn = itr->second.front();
    itr->second.pop_front();
    return (rtrn);
  }

  string rpush(vector<string>& args) {
    auto itr = my_lists.find(args[1]);
    if (itr == my_lists.end()) {
      list<string> new_list;
      size_t i = 1;
      while (++i < args.size()) {
        new_list.push_back(args[i]);
      }
      my_lists.insert(pair<string, list<string>>(args[1], new_list));
      string rtrn = "(integer) ";
      rtrn += (new_list.size() + '0');
      return (rtrn);
    }
    size_t i = 1;
    while (++i < args.size()) {
      itr->second.push_back(args[i]);
    }
    string rtrn = "(integer) ";
    rtrn += (itr->second.size() + '0');
    return (rtrn);
  }

  string rpop(string list_name) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return ("(nil)");
    }
    string rtrn = itr->second.back();
    itr->second.pop_back();
    return (rtrn);
  }

  string del(string key) {
    if (my_lists.find(key) != my_lists.end()) {
      my_lists.erase(key);
      return ("(integer) 1");
    }
    return ("(nil)");
  }

  string lrange(string list_name, int start, int end) {
    auto itr = my_lists.find(list_name);
    if (itr == my_lists.end() || itr->second.empty()) {
      return ("(empty list or set)");
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
      rtrn += '\n';
    }
    return (rtrn);
  }
};
