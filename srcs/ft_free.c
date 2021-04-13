/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:00:18 by jacher            #+#    #+#             */
/*   Updated: 2021/04/13 14:25:49 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void ft_free_token(t_list *token_list)
{
	t_list		*tmp;
	t_token		*tok;

	tmp = token_list;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		free(tok->tok_str);
		tmp = tmp->next;
	}
	ft_lstclear(&token_list, free);
}
