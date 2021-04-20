/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:26:04 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 11:06:17 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H

# define FT_H

#include <curses.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <wait.h>

#include "libft/libft.h"


#include "struct.h"

t_process	g_process;

int		execution_main(char *user_input, t_list **env_lst);

// ADCONSTA.H

#define ANSI_WHITE			"\E[0;37m"
#define ANSI_BOLD_WHITE		"\E[1;37m"
#define ANSI_BOLD_RED		"\E[1;31m"
#define ANSI_BOLD_YELLOW	"\E[1;33m"

char	*ft_strndup(char *src, int len);

// Prompt
char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt);
int		ft_update_log(char **screen, t_list *log, int fd_log);
void	ft_disable_raw_mode(struct termios *origin);
void	ft_enable_raw_mode(struct termios *origin);
void	ft_init_term_struct(t_term *term);
char	*ft_make_prompt(t_list **env_lst);
void	ft_move_cursor_home(t_term *term, char *prompt);

int		ft_down_arrow(char **screen, char **user_input, t_list *log, unsigned int *i);
int		ft_edit_line(char **screen, char *buf, unsigned int s_len);
int		ft_get_userinput(char **line, char *prompt, char *log_path);
int		ft_init_termcap(t_term *term);
int		ft_is_only_space(char *str);
int		ft_make_loglst(t_list **log, int fd);
int		ft_screen_wrapper(t_input *user, t_list *log);
int		ft_termcap_on(int c);
int		ft_up_arrow(char **screen, char **user_input, t_list *log, unsigned int *i);
int		ft_is_endofscreen(t_term *term, char *prompt);

// ENV
int		ft_make_envlst(t_list **head, char **envp);
char	**ft_make_ourenvp(t_list **env);
void	ft_lstclear_envlst(t_list **head);
char	*ft_getenv_name(char *env_str);
t_list	*ft_lstfind_env(t_list **begin, char *content_ref, int (*cmp)());
int		ft_lst_env_copy(t_list **dest, t_list **src);
void	ft_lst_env_sort(t_list **begin, int (*cmp)());
t_list	*ft_lstfind_export(t_list **begin, char *content_ref, int (*cmp)());
int		ft_update_pwd(char *new_path, t_list **env);

//Built in
int		ft_unset(t_list **env, char **argv, int pipe_mod);
int		ft_export(t_list **env, char **argv, int fd_out, int pipe_mod);
int		ft_cd(char **argv, t_list **env);

// Print
void	ft_print_prompt(t_term *term, char *prompt);
void	ft_print_str_table(char **av);
void	ft_print_str_lst(t_list *head);
void	ft_puttab(char **av);
void	ft_print_envlst_fd(t_list *env_head, int fd);
void	ft_print_exportlst_fd(t_list *env_head, int fd);

//Other
int		ft_find_cmd_path(char **job, char *exec, t_list **env);
char	*ft_my_getcwd(void);
int		ft_path_is_relative(char *str);
char	*ft_relative_to_absolute(char *exec);



//	JO.H
//promp et erreurs
void	print_str(char *str);
int		print_error(int errnum, char *error, int ret_wanted);
int		print_syntax_error(int errnum, char *error, int ret_wanted);
int		print_cmd_error(int errnum, t_list *error);

//print_help
void	print_list(t_list *list);
void	print_token(t_list *token);
void	print_cmd(t_list *cmd);
void	print_seq(t_seq *tab_seq, int seq_nb);

//ft free
void	ft_free_token(t_list *token_list);
void	ft_free_redir(t_list *redir_list);
void	ft_free_tab_seq(t_seq *tab_seq, int seq_nb);
void	ft_free_command(t_list *cmd_list);


//tokenize_utils
int		is_whitespace(char c);
int		comp(char c1, char c2);
void	escape_quote(char *str, int *pos);
int		look_second_quote(char c, char *str, int *pos);

//tokenize_assign
void	assign_type_1(t_list *token_list);
int		assign_type_2(t_list *head);
int 	assign_type_2_help(t_list **head, t_list **tmp, t_token *t2, t_token *t3);

//tokenize 
//t_list	*ft_get_token_list(t_list *token_list, char *input);
int		ft_get_token_list(t_list **token_list, char *input);

// sequence utils
int		get_seq_number(t_list *token_list);
void	set_up_pipe_number(t_seq *tab_seq, int cmd_nb, int pipe_pos);
void	init_setup(t_seq *tab_seq, t_seq **tmp, int *pipe_pos, int cmd_nb);

//sequence
t_seq	*create_sequence(t_seq *tab_seq, t_list *token_list, int seq_nb);

//expansion utils
int		is_word(char *str);
int		is_var_name(char c, int mod);
int		is_name(char *str);

//expansion manage
void	manage_quotes(t_expansion *exp, char c);
void	manage_escape(t_expansion *exp);
int		manage_variable(t_expansion *expi, t_list *var);
void	escape_within_doubles(t_expansion *exp);

//expansion find
int		count_final_str(t_expansion *exp, t_list *var);
int		find_variable_length(char *str, int start, int end, t_list *var);
char 	*find_variable_str(char *str, int start, int end, t_list *var);
char 	*assign_final_str(t_expansion *exp, t_list *var);

//expansion
void	escape_within_doubles(t_expansion *exp);
t_seq	*make_expansion(t_seq *tab_seq, t_list **var);

//command
t_list	*create_command(t_list *cmd_list, t_seq *tab_seq, int seq_nb, t_list **env);

//execute
void	update_fd_pipes(t_simple_cmd *tmp_c, t_pipe *p);
int		prepare_pipes(t_simple_cmd *tmp_c, t_pipe *p);

//built in
int		ft_echo(t_simple_cmd *cmd, t_pipe *p, int mod_n, int word);
int		ft_pwd(t_pipe *pipe, t_list **error);
int		ft_exit(t_simple_cmd *cmd, t_pipe *pipe, t_list **error);
int		execute_cmd(t_simple_cmd *tmp_c, t_list **env, t_list **error, t_pipe *p);

//built in
int		find_built_in(t_simple_cmd *cmd, t_pipe *pipe, t_list **error, t_list **env);



#include <term.h> 
#endif
