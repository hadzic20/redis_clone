#include "command_handler.hpp"

map<string, command> CommandHandler::functions = {
      {"set", set_handler},
      {"get", get_handler},
      {"del", del_handler},
      {"lindex", lindex_handler},
      {"lset", lset_handler},
      {"llen", llen_handler},
      {"lpop", lpop_handler},
      {"rpop", rpop_handler},
      {"lpush", lpush_handler},
      {"rpush", rpush_handler},
      {"lrange", lrange_handler},
  };