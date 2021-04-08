/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:59:35 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 21:58:27 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*dup;

	i = -1;
	len = ft_strlen(s1);
	dup = (char*)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (s1[++i])
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
