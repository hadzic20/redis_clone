#pragma once

#include "asio.hpp"
#include "hash.hpp"

vector<string> parse(string line);
string function_mapper(Hash* hash, vector<string> args);