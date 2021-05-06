/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:41:04 by adrien            #+#    #+#             */
/*   Updated: 2020/09/22 20:49:20 by adrien           ###   ########.fr       */
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
