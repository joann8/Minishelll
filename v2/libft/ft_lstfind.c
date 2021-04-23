/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:49:08 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 15:51:03 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *begin, void *content_ref, int (*cmp)())
{
	while (begin)
	{
		if (!((*cmp)(begin->content, content_ref)))
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}
