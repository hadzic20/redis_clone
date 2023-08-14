#include <iostream>
#include <vector>
#include "redis.hpp"

using namespace std;

class Mapper {
  public:
  typedef string (*command)(const vector<string>&, Hash* hash);
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
      string rtrn = "(error) wrong number of arguments (given ";
      rtrn += (args.size() - 1 + '0');
      rtrn += ", expected 1)";
      return (rtrn);
    }
    return (hash->get(args[1]));
  }

  string del_interface(vector<string>& args, Hash* hash) {
    if (args.size() < 2) {
      string rtrn = "(error) wrong number of arguments (given ";
      rtrn += (args.size() - 1 + '0');
      rtrn += ", expected 1)";
      return (rtrn);
    }
    return (hash->del(args[1]));
  }
};

string function_mapper(Hash* hash, vector<string> args) {
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
    return (my_mapper.del_interface(args, hash));
  }
  return ("(error) I'm sorry, I don't recognize that command");
}
