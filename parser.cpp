#include "redis.hpp"

vector<string> parse(string line) {
  size_t iterator = 0;
  size_t start = 0;
  vector<string> args;
  if (line == "") {
    args.push_back("");
    return (args);
  }
  while (iterator < line.length()) {
    while (line[iterator] == ' ' || line[iterator] == '\t') {
      iterator++;
    }
    if (line[iterator] == '"') {
      iterator++;
      start = iterator;
      while (line[iterator] != '"') {
        iterator++;
      }
      args.push_back(line.substr(start, (iterator - start)));
      iterator++;
      continue;
    }
    start = iterator;
    while (line[iterator] != ' ' && line[iterator] != '\t' && line[iterator] != '\0') {
      iterator++;
    }
    args.push_back(line.substr(start, (iterator - start)));
  }
  return (args);
}
