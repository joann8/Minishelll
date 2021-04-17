SRCS =	srcs/built_in.c			\
		srcs/built_in_echo.c	\
		srcs/built_in_pwd.c		\
		srcs/command.c			\
		srcs/execute_cmd.c		\
		srcs/expansion.c 		\
		srcs/expansion_find.c 		\
		srcs/expansion_manage.c 		\
		srcs/expansion_utils.c 		\
		srcs/ft_env_utils.c			\
		srcs/ft_find_cmd_path.c			\
		srcs/ft_free.c 				\
		srcs/ft_get_userinput.c 		\
		srcs/ft_make_envlst.c 		\
		srcs/ft_other_utils.c		\
		srcs/ft_path.c				\
		srcs/get_userinput_utils.c 	\
		srcs/adrien_main.c			\
		srcs/main.c					\
		srcs/print_help.c			\
		srcs/print_utils.c			\
		srcs/prompt_and_error.c		\
		srcs/sequence.c				\
		srcs/sequence_utils.c		\
		srcs/termcap_utils.c			\
		srcs/tokenize_assign.c		\
		srcs/tokenize.c				\
		srcs/tokenize_utils.c		

OBJ = $(SRCS:.c=.o)

NAME = minishell

CC = clang

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I ./libft/ -I ft.h

LIBS_PATH = -L ./libft 

LIBS = -lft -lncurses

#%.o: %.c
#	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

.c.o: ft.h  
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ) ft.h
	$(CC) $(CFLAGS) $(LIBS_PATH) $(OBJ) -o $(NAME) $(LIBS)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

	
