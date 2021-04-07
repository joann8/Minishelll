SRCS =  *.c

OBJ = $(SRCS:.c=.o)

NAME = a.out

CC = clang

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I . 

ALL_LIBS = -L ./libft/ -lft #-L -lncurses

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(ALL_LIBS)

$(OBJ):$(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

	
