/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:08:02 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:00:01 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	int		s_len;
	int		def_len;
	int		i;

	i = -1;
	new = NULL;
	if (s)
	{
		s_len = (int)ft_strlen(s);
		def_len = len;
		if ((int)start > s_len)
			def_len = 0;
		else if ((int)start + def_len > s_len)
			def_len = s_len - (int)start;
		new = (char *) malloc(sizeof(char) * (def_len + 1));
		if (!new)
			return (NULL);
		while (++i < def_len)
			new[i] = s[start + i];
		new[i] = '\0';
	}
	return (new);
}
