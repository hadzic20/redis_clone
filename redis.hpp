#pragma once

#include "asio.hpp"
#include "hash.hpp"
#include "list.hpp"

vector<string> parse(string line);
string function_mapper(List* list, Hash* hash, vector<string> args);