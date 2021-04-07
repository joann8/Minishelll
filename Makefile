SRCS =  main_adrien.c \
		utils_adrien.c

OBJ = $(SRCS:.c=.o)

NAME = a.out

CC = clang

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I . 

ALL_LIBS = -L ./libft/ -lft #-L -lncurses)


.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
all: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(ALL_LIBS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

	
