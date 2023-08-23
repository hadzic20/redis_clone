#pragma once

#include "command_handler.hpp"
#include "store.hpp"

vector<string> parse(string line);
string client_resp(char* request);
string server_resp(Store* store, string request);