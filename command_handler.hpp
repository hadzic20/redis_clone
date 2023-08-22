#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "return_value.hpp"
#include "store.hpp"

using namespace std;
typedef ReturnValue* (*command)(const vector<string>&, Store* store);

class CommandHandler {
  static ReturnValue* error(int given, int expected) {
    string rtrn = "wrong number of arguments (given ";
    rtrn += (given + '0');
    rtrn += ", expected ";
    rtrn += (expected + '0');
    rtrn += ")";
    return new Error(rtrn);
  }

  static ReturnValue* set_handler(const vector<string>& args, Store* store) {
    if (args.size() == 1) {
      return (store->set("", ""));
    }
    if (args.size() == 2) {
      return (store->set(args[1], ""));
    }
    return (store->set(args[1], args[2]));
  }

  static ReturnValue* get_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->get(args[1]));
  }

  static ReturnValue* del_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->del(args[1]));
  }

  static ReturnValue* lindex_handler(const vector<string>& args, Store* store) {
    if (args.size() < 3) {
      return (error(args.size() - 1, 2));
    }
    return (store->lindex(args[1], stoi(args[2])));
  }

  static ReturnValue* lset_handler(const vector<string>& args, Store* store) {
    if (args.size() < 4) {
      return (error(args.size() - 1, 3));
    }
    return (store->lset(args[1], stoi(args[2]), args[3]));
  }

  static ReturnValue* llen_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->llen(args[1]));
  }

  static ReturnValue* lpop_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->lpop(args[1]));
  }

  static ReturnValue* rpop_handler(const vector<string>& args, Store* store) {
    if (args.size() < 2) {
      return (error(args.size() - 1, 1));
    }
    return (store->rpop(args[1]));
  }

  static ReturnValue* lpush_handler(const vector<string>& args, Store* store) {
    if (args.size() < 3) {
      return new Error("wrong number of arguments for 'lpush' command");
    }
    return (store->lpush(args));
  }

  static ReturnValue* rpush_handler(const vector<string>& args, Store* store) {
    if (args.size() < 3) {
      return new Error("wrong number of arguments for 'rpush' command");
    }
    return (store->rpush(args));
  }

  static ReturnValue* lrange_handler(const vector<string>& args, Store* store) {
    if (args.size() < 4) {
      return (error(args.size() - 1, 3));
    }
    return (store->lrange(args[1], stoi(args[2]), stoi(args[3])));
  }

  static map<string, command> functions;

 public:
  static ReturnValue* command_handler(Store* store, const vector<string> args) {
    if (args.size() == 0) {
      return new MyString("blank line");
    }
    if (!args[0].compare("q")) {
      return new MyString("quit");
    }
    if (CommandHandler::functions.find(args[0]) ==
        CommandHandler::functions.end()) {
      return new Error("I'm sorry, I don't recognize that command");
    }
    return (CommandHandler::functions[args[0]](args, store));
  }
};
