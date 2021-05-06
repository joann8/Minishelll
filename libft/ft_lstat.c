/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:26:49 by adrien            #+#    #+#             */
/*   Updated: 2020/09/28 15:32:45 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *begin, unsigned int nbr)
{
	unsigned int	i;

	i = -1;
	while (begin && ++i <= nbr)
	{
		if (i == nbr)
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}
