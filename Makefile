SRCS = main.cpp parser.cpp command_handler.cpp

CC = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11

NAME = redis

all: $(NAME) client server

$(NAME):
	$(CC) $(CXXFLAGS) $(SRCS) -o $(NAME)

client:
	$(CC) $(CXXFLAGS) -DASIO_STANDALONE client.cpp command_handler.cpp client_resp.cpp parser.cpp -o client

server:
	$(CC) $(CXXFLAGS) -DASIO_STANDALONE server.cpp parser.cpp command_handler.cpp server_resp.cpp -o server
	
clean:
	rm -f $(NAME)
	
cleancs: 
	rm -f server
	rm -f client

fclean: clean cleancs
	
re: clean $(NAME)

recs: cleancs client server

.PHONY: all client server clean cleancs fclean re recs