/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:21:31 by jacher            #+#    #+#             */
/*   Updated: 2021/03/10 13:51:23 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

unsigned int	ft_strlen_gnl(char *str);
int				ft_chrn(char *str);
char			*ft_strjoin_gnl(char *s1, char *s2, int *res);
void			cpy_join(char *s1, char *s2, unsigned int l, unsigned int st);
void			cpy_update(char *s1, char *s2, unsigned int st);
void			ft_strdel(char **str);
int				get_next_line(int fd, char **line);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
