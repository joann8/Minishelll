/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:38:27 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 12:41:58 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;

	i = -1;
	s1_len = ft_strlen((const char*)s1);
	s2_len = ft_strlen(s2);
	while (++i < s2_len)
		s1[s1_len + i] = s2[i];
	s1[s1_len + i] = '\0';
	return (s1);
}
