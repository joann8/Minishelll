/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:27:19 by jacher            #+#    #+#             */
/*   Updated: 2021/04/22 18:24:33 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		create_sequence_help(t_seq *tab_seq, t_list *token_list,
			int seq_nb, int cmd_nb)
{
	t_list		*lst_tok;
	t_seq		*tmp;
	int			pipe_pos;
	int			res;

	lst_tok = token_list;
	while (cmd_nb < seq_nb)
	{
		init_setup(tab_seq, &tmp, &pipe_pos, cmd_nb);
		while (lst_tok)
		{
			res = seq_assign_sequence(&tmp, &lst_tok, &pipe_pos);
			if (res == 1)
				break ;
			if (res == -1)
			{
				ft_free_tab_seq(tab_seq, cmd_nb + 1);
				return (-1);
			}
		}
		set_up_pipe_number(tab_seq, cmd_nb, pipe_pos);
		cmd_nb++;
	}
	return (0);
}

t_seq	*create_sequence(t_seq *tab_seq, t_list *token_list, int seq_nb)
{
	if ((tab_seq = malloc(sizeof(t_seq) * (seq_nb + 1))) == NULL)
	{
		p_error(0, "malloc error\n", -1);
		return (NULL);
	}
	if (create_sequence_help(tab_seq, token_list, seq_nb, 0) == -1)
	{
		ft_free_tab_seq(tab_seq, seq_nb);
		return (NULL);
	}
	return (tab_seq);
}
