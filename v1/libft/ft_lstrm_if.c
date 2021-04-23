/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:52:15 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 15:53:20 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrm_if(t_list **b, void *cr, int (*cmp)(), void (*ffct)())
{
	t_list	*previous;
	t_list	*current;
	t_list	*next;

	current = *b;
	previous = NULL;
	while (current)
	{
		next = current->next;
		if (!((*cmp)(current->content, cr)))
		{
			(*ffct)(current->content);
			free(current);
			if (previous)
				previous->next = next;
			else if (next)
				*b = next;
		}
		else
			previous = current;
		current = next;
	}
}
