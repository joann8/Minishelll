/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 22:52:25 by louise            #+#    #+#             */
/*   Updated: 2020/09/21 14:45:21 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*need))
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		if (hay[i] == *need)
		{
			j = 0;
			while (hay[i + j] && need[j] && (i + j) < len
				&& hay[i + j] == need[j])
				j++;
			if (!(need[j]))
				return ((char *)(hay + i));
		}
		i++;
	}
	return (NULL);
}
