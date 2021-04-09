/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:27:19 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 10:52:13 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		get_seq_number(t_list *token_list)
{
	t_list	*tmp;
	int		count;

	tmp = token_list;
	count = 1;
	while (tmp)
	{
		if (((t_token *)tmp->content)->e_type == SEPARATOR
			&& tmp->next)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	set_up_pipe_number(t_seq *tab_seq, int cmd_nb, int pipe_pos)
{
	int		i;
	t_seq	*tmp;

	i = 0;
	tmp = &tab_seq[cmd_nb];
	while (i <= pipe_pos)
	{
		tmp->pipe_total = pipe_pos;
		tmp = tmp->next_pipe;
		i++;
	}
}

void	init_setup(t_seq *tab_seq, t_seq **tmp, int *pipe_pos, int cmd_nb)
{
	*pipe_pos = 0;
	(*tmp) = &tab_seq[cmd_nb];
	(*tmp)->pipe_pos = *pipe_pos;
	(*tmp)->word = NULL;
	(*tmp)->redir = NULL;
}
