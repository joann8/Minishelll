
SRCS =							\
		srcs/built_in.c			\
		srcs/built_in_cd.c		\
		srcs/built_in_echo.c	\
		srcs/built_in_exit.c	\
		srcs/built_in_export.c	\
		srcs/built_in_pwd.c		\
		srcs/built_in_unset.c	\
		srcs/command.c			\
		srcs/env_lst.c 			\
		srcs/env_utils.c		\
		srcs/execute_cmd.c		\
		srcs/execution_main.c	\
		srcs/expansion.c 		\
		srcs/expansion_find.c 	\
		srcs/expansion_manage.c \
		srcs/expansion_manage_utils.c \
		srcs/expansion_utils.c 	\
		srcs/search_exec_path.c	\
		srcs/free_utils.c 		\
		srcs/main.c				\
		srcs/other_utils.c		\
		srcs/print_help.c		\
		srcs/print_utils.c		\
		srcs/prompt.c			\
		srcs/error_management.c	\
		srcs/sequence.c			\
		srcs/sequence_assign.c	\
		srcs/sequence_utils.c	\
		srcs/termcap_utils.c	\
		srcs/tokenize.c			\
		srcs/tokenize_assign.c	\
		srcs/tokenize_utils.c	\
		srcs/userinput.c 		\
		srcs/userinput_utils.c 	

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

	
