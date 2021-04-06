/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:16:32 by jacher            #+#    #+#             */
/*   Updated: 2020/11/23 11:49:10 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ft_cinset(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;
	char			*str;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	if (!s1[0])
		return ("");
	while (ft_cinset(s1[start], set) == 1 && start < end)
		start++;
	while (ft_cinset(s1[end - 1], set) == 1 && start < end)
		end--;
	if (!(str = malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	while (i < end - start && s1[start + i])
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
