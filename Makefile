##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC= minishell.c 
	
	

NAME = mysh

CFLAGS=	$(HEAD) -Wall -Wextra

HEAD=	-Iinclude 

CC=	gcc -g $(CFLAGS)

RM=	rm -f

OBJ=	$(SRC:.c=.o)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: 	$(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re
