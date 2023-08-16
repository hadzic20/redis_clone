#include "redis.hpp"
#include <vector>
#include <string>

string server_resp(Store* store, string request) {
    size_t index = request.find_first_of("\r\n");
    size_t size = stoi(request.substr(1, index));
    unsigned int i = 0;
    unsigned int start, end = index;
    vector<string> args;
    while (i++ < size) {
        end += 3;
        start = end;
        string command = "";
        if (end >= request.size()) {
            break;
        }
        while (request[end] != '\r' && request[end + 1] != '\n') {
            end++;
        }
        unsigned int in_size = stoi(request.substr(start, end));
        end += 2;
        start = end;
        while ((end - start) < in_size) {
            command += request[end++];
        }
        args.push_back(command);
    }
    string answer = CommandHandler::command_handler(store, args);
    if (answer[0] == '+') {
        string rtrn = "\033[1;32m";
        rtrn += answer.substr(1, answer.size());
        rtrn += "\033[1;0m";
        return (rtrn);
    }
    if (answer[0] == '-') {
        string rtrn = "\033[1;31m";
        rtrn += answer.substr(1, answer.size());
        rtrn += "\033[1;0m";
        return (rtrn);
    }
    if (answer[0] == '$') {
        string rtrn = "\033[1;35m";
        rtrn += answer.substr(1, answer.size());
        rtrn += "\033[1;0m";
        return (rtrn);
    }
    if (answer[0] == ':') {
        string rtrn = "\033[1;33m";
        rtrn += answer.substr(1, answer.size());
        rtrn += "\033[1;0m";
        return (rtrn);
    }
    return (CommandHandler::command_handler(store, args));
}