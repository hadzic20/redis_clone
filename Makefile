SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

CC = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11
CPPFLAGS = -Wall -Werror -Wextra -std=c++11

NAME = redis

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJS)
	
clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean $(NAME)

.PHONY: all clean fclean re