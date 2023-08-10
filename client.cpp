#include <cstdlib>
#include <cstring>
#include <iostream>

#include "asio.hpp"

using asio::ip::tcp;

const int max_length = 1024;

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: ./client <host> <port>\n";
      return 1;
    }
    asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
        resolver.resolve(tcp::v4(), argv[1], argv[2]);
    tcp::socket s(io_context);
    asio::connect(s, endpoints);
    while (1) {
      std::cout << "> ";
      char request[max_length];
      std::cin.getline(request, max_length);
      if (!strcmp(request, "quit")) {
        break;
      }
      if (!strcmp(request, "")) {
        continue;
      }
      int i = strlen(request);
      while (i < max_length) {
        request[i++] = '\0';
      }
      asio::write(s, asio::buffer(request, max_length));
      char reply[max_length];
      asio::read(s, asio::buffer(reply, max_length));
      std::cout << reply << std::endl;
    }
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}