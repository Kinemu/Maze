##
## Makefile for projet in /home/mondol_a/Documents/piscine/Jour_3
## 
## Made by audrey mondoloni
## Login   <mondol_a@epitech.net>
## 
## Started on  Sat Jan 12 00:06:24 2013 audrey mondoloni
## Last update Sun Apr 13 15:47:52 2014 audrey mondoloni
##

CC	= g++ 

NAME	= Maze

SRC	= Maze.cpp

OBJ	= $(SRC:.cpp=.o)

RM	= rm -rf

CXXFLAGS = -W -Wall -Wextra -Werror -O3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re