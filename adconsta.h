/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adconsta.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:37 by calao             #+#    #+#             */
/*   Updated: 2021/04/10 10:08:58 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADCONSTA_H
# define ADCONSTA_H

char	*ft_read_input(int fd, int fd_log, t_term *term, t_list *log, unsigned int log_size);
void	ft_disable_raw_mode(struct termios *origin);
void	ft_enable_raw_mode(struct termios *origin);
void	ft_init_term_struct(t_term *term);
int		ft_init_termcap(t_term *term);
int		ft_termcap_on(int c);
void	ft_print_prompt(t_term *term);
int		ft_get_userinput(int fd_log, char **line, t_list *log);
void	ft_print_envlst(t_list *env_head);
void	ft_print_str_av(char **av);
int		ft_make_envlst(t_list **head, char **envp);
char	*ft_getenv_name(char *env_str);
char	*ft_strndup(char *src, int len);
void	ft_print_str_lst(t_list *head);
#endif
