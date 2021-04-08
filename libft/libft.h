/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:06:44 by louise            #+#    #+#             */
/*   Updated: 2020/12/22 15:41:39 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_atoi(const char *str);
char			*ft_strnstr(const char *hay, const char *need, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(const char *s, char c);
char			*ft_itoa(int n);
int				itoa_count_char(int n);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

long			ft_abs(int n);
int				ft_atoi_base(char *str, char *base);
int				ft_check_base(char *base);
int				ft_factorial(int nb);
int				ft_fibonacci(int index);
int				ft_find_next_prime(int nb);
int				ft_is_prime(int nb);
int				ft_islowcase(char c);
int				ft_isspace(char c);
int				ft_isupcase(char c);
char			*ft_joinstrs(int size, char **strs, char *sep);
int				ft_power(int nb, int power);
void			ft_print_int_tab(int *tab, int size);
void			ft_putchar(char c);
void			ft_putnbr(int n);
void			ft_putnbr_base(long nbr, char *base);
void			ft_putstr(char *str);
int				*ft_range(int min, int max);
void			ft_rev_int_tab(int *tab, int size);
void			ft_sort_int_tab(int *tab, int size);
char			**ft_split_charset(char *str, char *charset);
int				ft_sqrt(int nb);
char			*ft_strcapitalize(char *str);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strrev(const char *str);
char			*ft_strstr(const char *haystack, const char *needle);
void			ft_swap_int(int *a, int *b);
void			ft_swap_ptr(void **a, void **b);
char			*ft_itoa_base(long long n, char *base);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));

void			ft_lstrev(t_list **begin_list);
void			ft_lstmerge(t_list **begin_list1, t_list *begin_list2);
t_list			*ft_lstfind(t_list *begin, void *content_ref, int (*cmp)());
void			ft_lstrm_if(t_list **b, void *cr, int (*cmp)(), void (*ffct)());
void			ft_lstsort(t_list **begin, int (*cmp)());
t_list			*ft_lstat(t_list *begin, unsigned int nbr);
t_list			*ft_lstadd_strs(int size, char **strs);

int				get_next_line(int fd, char **line);
int				begin_line(char **line, char *buffer, int *offset);
int				fill_line(char **line, char *buffer, int *offset);
int				ft_strcmp(const char *s1, const char *s2);
void			*free_double_tab(char **tab);
#endif
