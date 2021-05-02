SRCS =										\
		srcs/built_in.c						\
		srcs/built_in_cd.c					\
		srcs/built_in_cd_utils.c			\
		srcs/built_in_cd_utils_two.c		\
		srcs/built_in_echo.c				\
		srcs/built_in_exit.c				\
		srcs/built_in_export.c				\
		srcs/built_in_export_utils.c		\
		srcs/built_in_pwd.c					\
		srcs/built_in_unset.c				\
		srcs/command_main.c					\
		srcs/command_main_redir.c			\
		srcs/command_main_words.c			\
		srcs/command_non_piped.c			\
		srcs/command_piped.c				\
		srcs/command_piped_utils.c			\
		srcs/command_utils.c				\
		srcs/env_lst_builder.c				\
		srcs/env_lst_utils.c				\
		srcs/execution_main.c				\
		srcs/expansion.c					\
		srcs/expansion_find.c				\
		srcs/expansion_manage.c				\
		srcs/expansion_manage_utils.c		\
		srcs/expansion_utils.c				\
		srcs/search_exec_path.c				\
		srcs/signals.c						\
		srcs/free_utils.c					\
		srcs/free_utils_bis.c				\
		srcs/main.c							\
		srcs/other_utils.c					\
		srcs/print_help.c					\
		srcs/print_utils.c					\
		srcs/prompt.c						\
		srcs/error_management.c				\
		srcs/sequence.c						\
		srcs/sequence_utils.c				\
		srcs/sequence_assign.c				\
		srcs/termcap_init_utils.c			\
		srcs/termcap_utils.c				\
		srcs/tokenize.c						\
		srcs/tokenize_assign.c				\
		srcs/tokenize_utils.c				\
		srcs/userinput.c					\
		srcs/userinput_utils.c				\
		srcs/userinput_utils_two.c 	

OBJ = $(SRCS:.c=.o)

NAME = minishell

CC = gcc 

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I ./libft/ -I . 

LIBS_PATH = -L ./libft 

LIBS = -lft -lncurses

LIB_FT = ./libft/libft.a

FT_H = ft.h

.c.o: $(FT_H) 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME): $(LIB_FT) $(FT_H) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS_PATH) $(OBJ) -o $(NAME) $(LIBS)

all: $(NAME)

$(LIB_FT):
	make libft.a -C ./libft/ 

clean:
	make clean -C ./libft/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft/
	rm -rf $(NAME)

re: fclean all
