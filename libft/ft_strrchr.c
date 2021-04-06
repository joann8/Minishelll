/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:30:34 by jacher            #+#    #+#             */
/*   Updated: 2020/11/22 16:16:59 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		res;
	int		i;
	char	*temp;

	res = -1;
	i = 0;
	temp = (char *)str;
	while (temp[i])
	{
		if ((unsigned char)temp[i] == (unsigned char)c)
			res = i;
		i++;
	}
	if ((unsigned char)temp[i] == (unsigned char)c)
		res = i;
	if (res >= 0)
		return (temp + res);
	else
		return (NULL);
}
