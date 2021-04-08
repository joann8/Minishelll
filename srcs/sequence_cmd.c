/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:27:19 by jacher            #+#    #+#             */
/*   Updated: 2021/04/08 19:37:45 by jacher           ###   ########.fr       */
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
		if (((t_token *)tmp->content)->e_type == SEPARATOR
			&& tmp->next)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int create_sequence(t_seq *tab_seq, t_list *token_list)
{
	int			seq_nb;
	t_list		*lst_tok;
	t_token		*tok;
	t_redir		*redir;
	t_seq		*tmp;
	int			cmd_nb;
	int 		pipe_pos;
	int			i;

	seq_nb = get_seq_number(token_list);
	printf("\nsequence number = %d\n\n", seq_nb);

	tab_seq = malloc(sizeof(t_seq) * (seq_nb + 1));
	if (tab_seq == NULL)
		return (-1); //erreur malloc
	printf ("malloc ok\n");	
	
	redir = NULL;	
	cmd_nb = 0;
	lst_tok = token_list;
	while (cmd_nb < seq_nb)
	{
		pipe_pos = 0;
		tmp = &tab_seq[cmd_nb];
		tmp->pipe_pos = pipe_pos;
		tmp->word = NULL;
		tmp->redir = NULL;
		while (lst_tok)
		{
			tok = (t_token*)lst_tok->content;
			if (tok->e_type == WORD)
				ft_lstadd_back(&tmp->word, ft_lstnew((void *)(tok->tok_str)));
			else if (tok->e_type == IN || tok->e_type == OUT || tok->e_type == APPEND)
			{
				redir = malloc(sizeof(t_redir));
				if (redir == NULL)
					return (-1); //erreur malloc
				redir->e_type = tok->e_type;
				lst_tok = lst_tok->next;
				redir->file_name = ft_strdup(((t_token*)(lst_tok->content))->tok_str);
				ft_lstadd_back(&tmp->redir, ft_lstnew((void *)(redir)));
			}
			else if (tok->e_type == PIPE)
			{
				pipe_pos++;
				tmp->next_pipe = malloc(sizeof(t_seq));
				if (tmp->next_pipe == NULL)
					return (-1); //erreur malloc
				tmp = tmp->next_pipe;
				tmp->pipe_pos = pipe_pos;
				tmp->word = NULL;
				tmp->redir = NULL;
				tmp->next_pipe = NULL;
			}
			else if (tok->e_type == SEPARATOR)
			{
				lst_tok = lst_tok->next;
				break ;
			}
			lst_tok = lst_tok->next;
		}
		i = 0;
		tmp = &tab_seq[cmd_nb];
		while (i <= pipe_pos)
		{
			tmp->pipe_total = pipe_pos;
			tmp = tmp->next_pipe;
			i++;
		}
		cmd_nb++;
	}
	print_seq(tab_seq, seq_nb);
	return (0);
}

