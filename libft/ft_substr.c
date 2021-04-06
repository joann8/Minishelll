/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:51:20 by jacher            #+#    #+#             */
/*   Updated: 2020/11/23 10:22:37 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
	{
		if (!(tab = malloc(sizeof(char))))
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	if (!(tab = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && s[i + (size_t)start])
	{
		tab[i] = s[i + (size_t)start];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
