/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adconsta.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:37 by calao             #+#    #+#             */
/*   Updated: 2021/04/14 12:37:03 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADCONSTA_H
# define ADCONSTA_H

char	*ft_getenv_name(char *env_str);
char	*ft_read_input(int fd, t_term *term, t_list *log);
char	*ft_strndup(char *src, int len);
char	*ft_strndup(char *src, int len);

int		ft_down_arrow(char **screen, char **user_input, t_list *log, unsigned int *i);
int		ft_edit_line(char **screen, char *buf, unsigned int s_len);
int		ft_get_userinput(char **line);
int		ft_init_termcap(t_term *term);
int		ft_is_only_space(char *str);
int		ft_make_envlst(t_list **head, char **envp);
int		ft_make_loglst(t_list **log, int fd);
int		ft_screen_wrapper(t_input *user, t_list *log);
int		ft_termcap_on(int c);
int		ft_up_arrow(char **screen, char **user_input, t_list *log, unsigned int *i);
int		ft_update_log(char **screen, t_list *log, int fd_log);

void	ft_disable_raw_mode(struct termios *origin);
void	ft_enable_raw_mode(struct termios *origin);
void	ft_init_term_struct(t_term *term);
void	ft_lstclear_envlst(t_list **head);
void	ft_print_envlst(t_list *env_head);
void	ft_print_prompt(t_term *term);
void	ft_puttab(char **av);
void	ft_print_str_lst(t_list *head);
void	ft_print_str_lst(t_list *head);
char	*ft_find_cmd_path(char *exec);


#endif
