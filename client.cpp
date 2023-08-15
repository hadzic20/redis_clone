#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "asio.hpp"
#include "redis.hpp"

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
    asio::error_code error;
    asio::connect(s, endpoints);
    while (1) {
      std::cout << "\033[1;32m> \033[1;0m";
      char request[max_length];
      std::cin.getline(request, max_length);
      if (!strcmp(request, "q")) {
        break;
      }
      if (!strcmp(request, "")) {
        continue;
      }
      string parsed_request = client_resp(request);
      size_t i = -1;
      while (++i < parsed_request.size()) {
        request[i] = parsed_request[i];
      }
      i = strlen(request);
      while (i < max_length) {
        request[i++] = '\0';
      }
      asio::write(s, asio::buffer(request, max_length));
      char reply[max_length];
      asio::read(s, asio::buffer(reply, max_length), error);
      std::cout << reply << std::endl;
    }
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}