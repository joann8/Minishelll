/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:59:20 by adrien            #+#    #+#             */
/*   Updated: 2020/09/22 19:05:24 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*el;

	el = (t_list*)malloc(sizeof(t_list));
	if (!el)
		return (NULL);
	el->content = content;
	el->next = NULL;
	return (el);
}
