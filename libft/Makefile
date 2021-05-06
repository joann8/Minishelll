SRCS=   	ft_memset.c			\
			ft_memcpy.c			\
			ft_bzero.c			\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_memccpy.c		\
			ft_memmove.c		\
			ft_strncmp.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_strlen.c			\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isascii.c		\
			ft_isprint.c		\
			ft_strlcpy.c		\
			ft_strnstr.c		\
			ft_calloc.c			\
			ft_strdup.c			\
			ft_substr.c			\
			ft_strjoin.c		\
			ft_strtrim.c		\
			ft_split.c			\
			ft_itoa.c			\
			ft_strmapi.c		\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_strlcat.c		\
			ft_atoi.c			\
			ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c			\
			ft_is_prime.c		\
			ft_putnbr_base.c	\
			ft_islowcase.c		\
			ft_putstr.c			\
			ft_isspace.c		\
			ft_range.c			\
			ft_isupcase.c		\
			ft_rev_int_tab.c	\
			ft_joinstrs.c		\
			ft_sort_int_tab.c	\
			ft_lstadd_strs.c	\
			ft_split_charset.c	\
			ft_lstat.c			\
			ft_sqrt.c			\
			ft_lstfind.c		\
			ft_strcapitalize.c	\
			ft_abs.c			\
			ft_lstmerge.c		\
			ft_strcat.c			\
			ft_atoi_base.c		\
			ft_lstrev.c			\
			ft_strcpy.c			\
			ft_lstrm_if.c		\
			ft_strncat.c		\
			ft_check_base.c		\
			ft_lstsort.c		\
			ft_strncpy.c		\
			ft_power.c			\
			ft_strrev.c			\
			ft_factorial.c		\
			ft_print_int_tab.c	\
			ft_strstr.c			\
			ft_fibonacci.c		\
			ft_putchar.c		\
			ft_swap_int.c		\
			ft_find_next_prime.c\
			ft_putnbr.c			\
			ft_swap_ptr.c		\
			get_next_line.c		\
			ft_strcmp.c			\
			ft_free_double_tab.c

OBJS=       ${SRCS:.c=.o}
HEAD=		libft.h
CC=			gcc
CFLAGS=		-Wall -Werror -Wextra
NAME=		libft.a

.c.o:		
	${CC} ${CFLAGS} -include ${HEAD} -c $< -o ${<:.c=.o}
$(NAME):	${OBJS}
	ar -rcs ${NAME} ${OBJS}
all: ${NAME}
clean:
	rm -rf ${OBJS}
fclean: clean
	rm -rf ${NAME}
re: fclean all
.PHONY: all clean fclean re bonus
