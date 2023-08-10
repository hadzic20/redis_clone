#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>

#include "asio.hpp"
#include "redis.hpp"

using asio::ip::tcp;

const int max_length = 1024;

void session(tcp::socket sock) {
  try {
    Hash hash;
    while (1) {
      char data[max_length];
      asio::error_code error;
      read(sock, asio::buffer(data), error);
      if (error == asio::error::eof)
        break;
      else if (error)
        throw asio::system_error(error);
      vector<string> args = parse(data);
      string tmp = function_mapper(&hash, args);
      if (tmp == "quit") {
        break;
      } else if (tmp == "blank line") {
        continue;
      } else {
        int i = -1;
        while (tmp[++i]) data[i] = tmp[i];
        while (i < max_length) {
          data[i++] = '\0';
        }
        asio::write(sock, asio::buffer(data, max_length));
      }
    }
  } catch (std::exception& e) {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(asio::io_context& io_context, unsigned short port) {
  tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
  while (1) {
    std::thread(session, a.accept()).detach();
  }
}

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: ./server <port>\n";
      return 1;
    }
    asio::io_context io_context;
    server(io_context, std::atoi(argv[1]));
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}