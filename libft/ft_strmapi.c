/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:52:17 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:15:58 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	s_len;
	unsigned int	i;

	s_len = 0;
	i = -1;
	result = NULL;
	if (s)
	{
		s_len = ft_strlen(s);
		result = (char*)malloc(sizeof(char) * (s_len + 1));
		if (!result)
			return (NULL);
		while (++i < s_len)
			result[i] = (*f)(i, s[i]);
		result[i] = '\0';
	}
	return (result);
}
