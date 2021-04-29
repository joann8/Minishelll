/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:39:53 by adrien            #+#    #+#             */
/*   Updated: 2020/09/28 15:41:35 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_strs(int size, char **strs)
{
	int		i;
	t_list	*begin;
	t_list	*previous;

	i = -1;
	previous = NULL;
	while (++i < size)
	{
		begin = ft_lstnew(strs[i]);
		begin->next = previous;
		previous = begin;
	}
	return (begin);
}
