SRCS = $(wildcard *.c)

OBJ = $(SRCS:.c=.o)

NAME = a.out

CC = clang

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I . 

LFT = -L ../libft/ -lft

LCURSES = -L -lncurses

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

	
