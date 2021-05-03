/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:26:04 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 23:22:08 by calao            ###   ########.fr       */
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

t_process	g;

int		execution_main(char *user_input, t_list **env_lst);

// ADCONSTA.H

#define ANSI_WHITE			"\E[0;37m"
#define ANSI_BOLD_WHITE		"\E[1;37m"
#define ANSI_BOLD_RED		"\E[1;31m"
#define ANSI_BOLD_YELLOW	"\E[1;33m"


// Prompt
void	ft_print_prompt(t_term *term, char *prompt);
char	*ft_make_prompt(t_list **env_lst);

//Userinput
int		ft_get_userinput(char **line, char *prompt, char *log_path, int *ret);
char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt);
void	ft_enable_raw_mode(struct termios *origin);
void	ft_disable_raw_mode(struct termios *origin);
int		ft_update_log(char **screen, t_list *log, int fd_log);
int		ft_make_loglst(t_list **log, int fd);

//Userinput handling

int		ft_screen_wrapper(t_input *user, t_list *log);
int		ft_edit_line(char **screen, char *buf, unsigned int s_len);
int		ft_up_arrow(char **screen, char **user_input, t_list *log, unsigned int *i);
int		ft_down_arrow(char **screen, char **user_input, t_list *log, unsigned int *i);

//Termcaps
int		ft_init_termcap(t_term *term);
void	ft_init_term_struct(t_term *term);
int		ft_termcap_on(int c);

	// Curseur
int		ft_is_endofscreen(t_term *term, char *prompt, t_input *user);
void	ft_move_cursor_home(t_term *term, char *prompt);
int		ft_getcursorxy(int *row, int *col);


// ENV 
int		ft_make_envlst(t_list **head, char **envp);
char	*ft_getenv_name(char *env_str);
char	*ft_fuse_var(t_var *var);
char	**ft_make_ourenvp(t_list **env);

	//env_lst_utils
t_list	*ft_lstfind_env(t_list **begin, char *content_ref, int (*cmp)());
int		ft_lst_env_copy(t_list **dest, t_list **src);
void	ft_lst_env_sort(t_list **begin, int (*cmp)());
void	ft_lstclear_envlst(t_list **head);
t_list	*ft_env_node_copy(t_var *v_src);



//Built in
int		ft_unset(t_simple_cmd *cmd, t_list **env, char **argv);
			//cd
int		ft_cd(t_simple_cmd *cmd, t_list **env);
int		is_absolute_path(char *str);
void	ft_lstdel_last(t_list **head);
char	*ft_get_absolute_path(t_list *dir);
char	*get_newpath(char *operand);
int		ft_cd_error(char *s1, char *s2, int w_return);
int		ft_make_dir_lst(t_list **dir, char *str);
int		ft_edit_dir_lst(t_list **dir, char *r_path);
int		fake_cd(char *new_path);
int		ft_search_dir(char *exec, char *dir_path);
char	*ft_cd_path(char *operand, t_list **env);


			//export
int		ft_export(t_list **env, t_simple_cmd *cmd, int fd_out);
t_list	*ft_lstfind_export(t_list **begin, char *content_ref, int (*cmp)());
int		ft_update_pwd(char *new_path, t_list **env);
int		ft_lst_env_addback(t_list **env, char *argv);
t_list	*ft_allocate_env_node(char *argv, int i, int j, int mode);
t_var	*ft_allocate_env_var_struct(char *argv, int i, int j, int mode);
int		ft_check_export_name(char *str);


// Print
void	ft_print_str_table(char **av);
void	ft_print_str_lst(t_list *head);
void	ft_puttab(char **av);
void	ft_print_envlst_fd(t_list *env_head, int fd);
void	ft_print_exportlst_fd(t_list *env_head, int fd);
int		print_err(char *str1, char *str2, char *str3, int ret_wanted);

//Other
int		ft_path_is_relative(char *str);
int		ft_search_job_path(char **job_output, char *exec_input, t_list **env);
char	*get_newpath(char *operand);

	//other_utils
int		ft_is_only_space(char *str);
char	*ft_strndup(char *src, int len);
void	ft_swap_content(t_list *a, t_list *b);
int		ft_lst_on_env_size(t_list **env);
int		ft_is_file_executable(char *filepath);

	//Signals
void	read_ctrl_c(int signum);
void	read_ctrl_quit(int signum);
void	exec_ctrl_c(int signum);
void	exec_ctrl_quit(int signum);
//



//	JO.H
//promp et erreurs
int		p_error(int errnum, char *error, int ret_wanted);
int		print_syntax_error(int ret_wanted);
int		print_err_pipe(char *str1, char *str2, char *str3, int ret_wanted);

//print_help
void	print_list(t_list *list);
void	print_token(t_list *token);
void	print_cmd(t_list *cmd);
void	print_cmd_piped(t_simple_cmd *cmd);
void	print_seq(t_seq *tab_seq, int seq_nb);

//ft free
void	ft_free_token(t_list *token_list);
void	ft_free_redir(t_list *redir_list);
void	ft_free_tab_seq(t_seq *tab_seq, int seq_nb);
void	ft_free_command(t_list *cmd_list);
void	ft_free_command_list(t_simple_cmd *cmd_list);
int		ft_free(void *str, int wanted_return);


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
int		seq_assign_sequence(t_seq **tmp, t_list **lst_tok, int *pipe_pos);
t_seq	*create_sequence(t_seq *tab_seq, t_list *token_list, int seq_nb);

//expansion utils
int		is_word(char *str);
int		is_var_name(char c, int mod);
int		is_name(char *str);
void	ft_copy_loc_expansion(char *tofind, char *str, int start, int end);

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
void	manage_quotes(t_expansion *exp, char c);
void	manage_escape(t_expansion *exp);
void	escape_within_doubles(t_expansion *exp);
char	*modify_str(char *str, t_list **var);
int		make_expansion(t_seq *tab_seq, t_list **var);

//command_pipe_exec
int		prepare_pipe_execution(t_simple_cmd *tmp_c, t_pipe *p, int ret);
void	update_fd_pipes(t_simple_cmd *tmp_c, t_pipe *p, int ret);

//command_pipe_utils
void	assign_pipes(t_seq *seq, t_simple_cmd *cmd);
int		assign_list_word(t_seq *seq, t_simple_cmd *cmd, t_list **env);
int		assign_list_redir(t_list *tmp_l, t_simple_cmd *cmd, t_list **env);
int		expand_list_redir(t_list *begin, t_list **var);
int		prepare_execution(int ***fd_pipe, int **pid_list, int size);

//command main assign utils
char *trim_spaces_for_echo(char *new_str, int i, int j, int mod);
int	check_redir_expansion(t_simple_cmd *cmd, t_redir *r, t_list **env);

//command_simple
int		create_command(t_seq *tab_seq, int seq_nb, t_list **env);

//built in
int		ft_echo(t_simple_cmd *cmd, t_pipe *p, int mod_n, int word);
int		ft_pwd(t_pipe *pipe);
int		ft_exit(t_simple_cmd *cmd, t_pipe *pipe);
int		execute_non_piped(t_simple_cmd *tmp_c, t_list **env);
int		execute_cmd_non_piped(t_simple_cmd *tmp_c, t_list **env);
int		execute_piped(t_simple_cmd *tmp_c, t_list **env);

//built in
int		find_built_in(t_simple_cmd *cmd, t_list **env);

int	execute_cmd_path_not_found(t_simple_cmd *tmp_c, int ret);

//command piped utils
void 	close_fd_pipe(int ***fd_pipe, int size, int mod);
int 	prepare_fd_pipe(int ***fd_pipe, int size);
void 	clear_fd_pipe(int ***fd_pipe, int index, int mod);
int		set_up_child_pipes(t_simple_cmd *tmp_c, int size, int ***fd_pipe, int i);

#include <term.h> 
#endif
