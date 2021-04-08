/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:41:04 by louise            #+#    #+#             */
/*   Updated: 2020/09/22 20:49:20 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*track;
	t_list	*next;

	track = *lst;
	while (track)
	{
		next = track->next;
		track->next = NULL;
		if (track->content)
			(*del)(track->content);
		free(track);
		track = next;
	}
	*lst = NULL;
}
