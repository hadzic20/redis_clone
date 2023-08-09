#include "redis.hpp"

string function_mapper(Hash* hash, vector<string> args) {
  if (args.size() == 0)
    return ("blank line");
  else if (!args[0].compare("q"))
    return ("quit");
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