/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:34:34 by louise            #+#    #+#             */
/*   Updated: 2020/12/31 05:42:57 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_wd(const char *s, char c)
{
	int		nb_wd;
	char	p_char;
	int		i;

	nb_wd = 0;
	p_char = -1;
	i = 0;
	while (s && s[i])
	{
		if ((p_char == -1 || p_char == c) && s[i] != c)
			nb_wd++;
		p_char = s[i];
		i++;
	}
	return (nb_wd);
}

static char	*set_wd(const char *s, char c, int start_index)
{
	char	*wd;
	int		wd_len;
	int		i;

	i = -1;
	wd_len = 0;
	while (s[start_index + wd_len] && s[start_index + wd_len] != c)
		wd_len++;
	wd = (char*)malloc(sizeof(char) * (wd_len + 1));
	if (!wd)
		return (NULL);
	while (++i < wd_len)
		wd[i] = s[start_index + i];
	wd[i] = '\0';
	return (wd);
}

char	**ft_split(const char *s, char c)
{
	char	**wd_tab;
	char	p_char;
	int		i;
	int		wd_index;

	i = 0;
	wd_index = 0;
	p_char = -1;
	wd_tab = (char**)malloc(sizeof(char*) * (count_wd(s, c) + 1));
	if (!wd_tab)
		return (NULL);
	while (s && s[i])
	{
		if ((p_char == -1 || p_char == c) && s[i] != c)
		{
			wd_tab[wd_index] = set_wd(s, c, i);
			if (!wd_tab[wd_index])
				return (free_double_tab(wd_tab));
			wd_index++;
		}
		p_char = s[i];
		i++;
	}
	wd_tab[wd_index] = NULL;
	return (wd_tab);
}
