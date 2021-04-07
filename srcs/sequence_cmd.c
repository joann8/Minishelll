/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:27:19 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 19:52:19 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int	get_seq_number(t_list *token_list)
{
	t_list	*tmp;
	int		count;

	tmp = token_list;
	count = 1;
	while (tmp)
	{
		if (((t_token *)tmp->content)->e_type == SEPARATOR)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int  create_sequence(t_seq *tab_seq, t_list *token_list)
{
	int			seq_nb;
/*	t_list		*tmp;
	t_seq		*tmp2;
	int			cmd_nb;
	int 		pipe_pos;*/

	(void)tab_seq;
	seq_nb = get_seq_number(token_list);
	return(printf("sequence number = %d\n", seq_nb));
/*	tab_seq = malloc(sizeof(t_seq) * (seq_nb + 1));
	if (tab_seq == NULL)
		return (-1); //erreur malloc
	cmd_nb = 0;
	tmp = token_list;
	tmp2 = tab_seq[cmd_nb];
	pipe_pos = 0;
	while (tmp)
	{
		if (ft_strncmp(";", (char *)tmp->content, 2) == 0)
		{
			tmp = tmp->next;
			cmd_nb++;
			tmp2 = tab_seq[cmd_nb];
		}
		else
		{
			if (ft_strncmp("|", (char *)tmp->content, 2) == 0)
			{
				pipe_pos++;
				tmp = tmp->next;

				
			}

			else 


		}
				
	}	
	*/
	
}

