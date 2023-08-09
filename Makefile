SRCS = main.cpp parser.cpp function_mapper.cpp

CC = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11

NAME = redis

all: $(NAME) client server

$(NAME):
	$(CC) $(SRCS) $(CXXFLAGS) -o $(NAME)

client:
	g++ -Wall -Werror -Wextra -DASIO_STANDALONE -std=c++11 client.cpp -o client

server:
	g++ -Wall -Werror -Wextra -DASIO_STANDALONE -std=c++11 server.cpp parser.cpp function_mapper.cpp -o server
	
clean:
	rm -f $(NAME)
	
cleancs: 
	rm -f server
	rm -f client

fclean: clean cleancs
	
re: clean $(NAME)

recs: cleancs client server

.PHONY: all client server clean cleancs fclean re recs