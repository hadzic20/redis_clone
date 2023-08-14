#include <iostream>
#include <vector>

#include "redis.hpp"

using namespace std;

class Mapper {
 public:
  typedef string (*command)(const vector<string>&, Hash* hash);
  string error(int given, int expected) {
    string rtrn = "(error) wrong number of arguments (given ";
    rtrn += (given + '0');
    rtrn += ", expected ";
    rtrn += (expected + '0');
    rtrn += ")";
    return (rtrn);
  }
  string set_interface(vector<string>& args, Hash* hash) {
    if (args.size() == 1) {
      return (hash->set("", ""));
    }
    if (args.size() == 2) {
      return (hash->set(args[1], ""));
    }
    return (hash->set(args[1], args[2]));
  }

  string get_interface(vector<string>& args, Hash* hash) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (hash->get(args[1]));
  }

  string del_interface(vector<string>& args, Hash* hash, List* list) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    string rtrn = hash->del(args[1]);
    if (!rtrn.compare("(nil)")) {
      rtrn = list->del(args[1]);
    }
    return (rtrn);
  }

  string lindex_interface(vector<string>& args, List* list) {
    if (args.size() < 3) {
      return (error(args.size() - 1, 2));
    }
    return (list->lindex(args[1], stoi(args[2])));
  }

  string lset_interface(vector<string>& args, List* list) {
    if (args.size() < 4) {
      return (error(args.size() - 1, 3));
    }
    return (list->lset(args[1], stoi(args[2]), args[3]));
  }

  string llen_interface(vector<string>& args, List* list) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (list->llen(args[1]));
  }

  string lpop_interface(vector<string>& args, List* list) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (list->lpop(args[1]));
  }

  string rpop_interface(vector<string>& args, List* list) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (list->rpop(args[1]));
  }

  string lpush_interface(vector<string>& args, List* list) {
    if (args.size() < 3) {
      return ("(error) ERR wrong number of arguments for 'lpush' command");
    }
    return (list->lpush(args));
  }

  string rpush_interface(vector<string>& args, List* list) {
    if (args.size() < 3) {
      return ("(error) ERR wrong number of arguments for 'rpush' command");
    }
    return (list->rpush(args));
  }

  string lrange_interface(vector<string>& args, List* list) {
    if (args.size() < 4) {
      return (error(args.size() - 1, 3));
    }
    return (list->lrange(args[1], stoi(args[2]), stoi(args[3])));
  }
};

string function_mapper(List* list, Hash* hash, vector<string> args) {
  Mapper my_mapper;
  if (args.size() == 0) {
    return ("blank line");
  }
  if (!args[0].compare("q")) {
    return ("quit");
  }
  if (!args[0].compare("set")) {
    return (my_mapper.set_interface(args, hash));
  }
  if (!args[0].compare("get")) {
    return (my_mapper.get_interface(args, hash));
  }
  if (!args[0].compare("del")) {
    return (my_mapper.del_interface(args, hash, list));
  }
  if (!args[0].compare("lpush")) {
    return (my_mapper.lpush_interface(args, list));
  }
  if (!args[0].compare("lpop")) {
    return (my_mapper.lpop_interface(args, list));
  }
  if (!args[0].compare("rpush")) {
    return (my_mapper.rpush_interface(args, list));
  }
  if (!args[0].compare("rpop")) {
    return (my_mapper.rpop_interface(args, list));
  }
  if (!args[0].compare("lindex")) {
    return (my_mapper.lindex_interface(args, list));
  }
  if (!args[0].compare("lset")) {
    return (my_mapper.lset_interface(args, list));
  }
  if (!args[0].compare("llen")) {
    return (my_mapper.llen_interface(args, list));
  }
  if (!args[0].compare("lrange")) {
    return (my_mapper.lrange_interface(args, list));
  }
  return ("(error) I'm sorry, I don't recognize that command");
}
