/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:41:57 by louise            #+#    #+#             */
/*   Updated: 2020/09/24 11:35:43 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c_var;
	unsigned char	*s_uc;
	size_t			i;

	c_var = (unsigned char)c;
	s_uc = (unsigned char*)s;
	i = -1;
	while (++i < n)
		if (s_uc[i] == c_var)
			return ((void *)(s + i));
	return (NULL);
}
