#include "hash.h"

string* parse(string line) {
  int iterator = 0;
  int index = 0;
  string* args = new string[line.length()];
  if (line == "") {
    return (NULL);
  }
  while (line[iterator] != '\0') {
    while (line[iterator] == ' ' || line[iterator] == '\t') {
      iterator++;
    }
    if (line[iterator] == '"') {
      iterator++;
      while (line[iterator] != '"') {
        args[index] += line[iterator++];
      }
      iterator++;
      index++;
      continue;
    }
    while (line[iterator] != ' ' && line[iterator] != '\t' && line[iterator] != '\0') {
      args[index] += line[iterator++];
    }
    index++;
  }
  return (args);
}

string function_mapper(Hash* hash, string* args) {
  if (!args[0].compare("q"))
    return ("quit");
  else if (!args[0].compare(""))
    return ("blank line");
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