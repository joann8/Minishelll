/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:55:19 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 16:48:40 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_content(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	ft_lstsort(t_list **begin, int (*cmp)())
{
	t_list	*current;
	t_list	*next;

	current = *begin;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if ((*cmp)(current->content, next->content) > 0)
				ft_swap_content(current, next);
			next = next->next;
		}
		current = current->next;
	}
}
