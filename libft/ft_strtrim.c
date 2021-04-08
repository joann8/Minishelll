/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:00:39 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:07:47 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	char_to_rmv(const char *s1, const char *set, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nb;

	i = 0;
	j = 0;
	nb = 0;
	while (s1[i] && is_charset(s1[i], set))
	{
		nb++;
		i++;
	}
	if (i != ft_strlen(s1))
	{
		while (len >= j + 1 && is_charset(s1[len - j - 1], set))
		{
			nb++;
			j++;
		}
	}
	return (nb);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new;
	size_t	i;
	size_t	start_index;
	size_t	char_to_copy;
	size_t	len;

	i = -1;
	start_index = 0;
	new = NULL;
	if (s1)
	{
		len = ft_strlen(s1);
		char_to_copy = len - char_to_rmv(s1, set, len);
		new = (char*)malloc(sizeof(char) * (char_to_copy + 1));
		if (!new)
			return (NULL);
		while (s1[start_index] && is_charset(s1[start_index], set))
			start_index++;
		while (++i < char_to_copy)
			new[i] = s1[start_index + i];
		new[i] = '\0';
	}
	return (new);
}
