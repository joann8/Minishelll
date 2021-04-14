SRCS = $(wildcard *.c)

OBJ = $(SRCS:.c=.o)

NAME = a.out

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

INCLUDE = -I . 

LFT = -L ../libft/ -lft

LCURSES = -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFT) $(LCURSES)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

	
