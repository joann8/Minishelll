/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:24:39 by jacher            #+#    #+#             */
/*   Updated: 2021/03/10 13:51:47 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

unsigned int	ft_strlen_gnl(char *str)
{
	unsigned int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				ft_chrn(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void			cpy_update(char *src, char *str, unsigned int st)
{
	unsigned int j;

	j = 0;
	while (src[st + j])
	{
		str[j] = src[j + st];
		j++;
	}
	str[j] = '\0';
}

void			cpy_join(char *src, char *str, unsigned int l, unsigned int st)
{
	unsigned int j;

	j = 0;
	while (j < l)
	{
		str[j + st] = src[j];
		j++;
	}
	str[j + st] = '\0';
}

char			*ft_strjoin_gnl(char *s1, char *s2, int *res)
{
	unsigned int	s_s1;
	unsigned int	s_s2;
	char			*tab;

	if (!s1 && !s2)
		return (NULL);
	s_s1 = ft_strlen_gnl(s1);
	s_s2 = ft_strlen_gnl(s2);
	if (!(tab = malloc(sizeof(char) * (s_s1 + s_s2 + 1))))
	{
		*res = -1;
		return (NULL);
	}
	cpy_join(s1, tab, s_s1, 0);
	cpy_join(s2, tab, s_s2, s_s1);
	free(s1);
	return (tab);
}
