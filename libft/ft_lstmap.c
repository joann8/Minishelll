/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 21:07:57 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:29:45 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *),	void (*del)(void *))
{
	t_list	*begin;
	t_list	*previous;
	t_list	*new;

	begin = NULL;
	previous = NULL;
	if (l)
	{
		while (l)
		{
			new = ft_lstnew((*f)(l->content));
			if (!new)
			{
				ft_lstclear(&begin, del);
				return (NULL);
			}
			if (!begin)
				begin = new;
			if (previous)
				previous->next = new;
			previous = new;
			l = l->next;
		}
	}
	return (begin);
}
