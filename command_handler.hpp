#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "store.hpp"

using namespace std;
typedef string (*command)(const vector<string>&, Store* store);

class CommandHandler {
  static string error(int given, int expected) {
    string rtrn = "(error) wrong number of arguments (given ";
    rtrn += (given + '0');
    rtrn += ", expected ";
    rtrn += (expected + '0');
    rtrn += ")";
    return (rtrn);
  }

  static string set_handler(const vector<string>& args, Store* store) {
    if (args.size() == 1) {
      return (store->set("", ""));
    }
    if (args.size() == 2) {
      return (store->set(args[1], ""));
    }
    return (store->set(args[1], args[2]));
  }

  static string get_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->get(args[1]));
  }

  static string del_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->del(args[1]));
  }

  static string lindex_handler(const vector<string>& args, Store* store) {
    if (args.size() < 3) {
      return (error(args.size() - 1, 2));
    }
    return (store->lindex(args[1], stoi(args[2])));
  }

  static string lset_handler(const vector<string>& args, Store* store) {
    if (args.size() < 4) {
      return (error(args.size() - 1, 3));
    }
    return (store->lset(args[1], stoi(args[2]), args[3]));
  }

  static string llen_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->llen(args[1]));
  }

  static string lpop_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->lpop(args[1]));
  }

  static string rpop_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->rpop(args[1]));
  }

  static string lpush_handler(const vector<string>& args, Store* store) {
    if (args.size() < 3) {
      return ("(error) ERR wrong number of arguments for 'lpush' command");
    }
    return (store->lpush(args));
  }

  static string rpush_handler(const vector<string>& args, Store* store) {
    if (args.size() < 3) {
      return ("(error) ERR wrong number of arguments for 'rpush' command");
    }
    return (store->rpush(args));
  }

  static string lrange_handler(const vector<string>& args, Store* store) {
    if (args.size() < 4) {
      return (error(args.size() - 1, 3));
    }
    return (store->lrange(args[1], stoi(args[2]), stoi(args[3])));
  }

  static map<string, command> functions;

 public:
  static string command_handler(Store* store, const vector<string> args) {
    if (args.size() == 0) {
      return ("blank line");
    }
    if (!args[0].compare("q")) {
      return ("quit");
    }
    if (CommandHandler::functions.find(args[0]) ==
        CommandHandler::functions.end()) {
      return ("(error) I'm sorry, I don't recognize that command");
    }
    return (CommandHandler::functions[args[0]](args, store));
  }
};
