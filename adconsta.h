/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adconsta.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:37 by calao             #+#    #+#             */
/*   Updated: 2021/04/09 13:20:28 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADCONSTA_H
# define ADCONSTA_H

char	*ft_read_input(int fd, t_term *term);
void	ft_disable_raw_mode(struct termios *origin);
void	ft_enable_raw_mode(struct termios *origin);
void	ft_init_term_struct(t_term *term);
int		ft_init_termcap(t_term *term);
int		ft_termcap_on(int c);
void	ft_print_prompt(t_term *term);
int		ft_get_userinput(char **line);

#endif
