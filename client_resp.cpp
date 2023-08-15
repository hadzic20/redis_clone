#include "redis.hpp"
#include <vector>
#include <string>

string client_resp(char* request) {
    size_t i = -1;
    string req;
    vector<string> args;
    while (request[++i] != '\0') {
        req += request[i];
    }
    args = parse(req);
    req = "*";
    req += to_string(args.size());
    req += "\r\n";
    i = -1;
    while (++i < args.size()) {
        req += "$";
        req += args[i];
        req += "\r\n";
    }
    req += "\0";
    return (req);
}