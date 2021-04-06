/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:07:34 by jacher            #+#    #+#             */
/*   Updated: 2020/11/09 19:16:32 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*tofind)
		return ((char*)src);
	if (len == 0)
		return (NULL);
	while (src[i] && i < len)
	{
		if (src[i] == tofind[0])
		{
			j = 1;
			while (src[i + j] == tofind[j] && tofind[j] && i + j < len)
				j++;
			if (tofind[j] == '\0')
				return ((char *)src + i);
		}
		i++;
	}
	return (NULL);
}
