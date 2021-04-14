/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:00:18 by jacher            #+#    #+#             */
/*   Updated: 2021/04/14 19:16:25 by calao            ###   ########.fr       */
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
}

void ft_free_redir(t_list *redir_list)
{
	t_list		*tmp;
	t_redir		*red;

	tmp = redir_list;
	while (tmp)
	{
		red = (t_redir *)tmp->content;
		free(red->file_name);
		tmp = tmp->next;
	}
}

void ft_free_tab_seq(t_seq *tab_seq, int seq_nb)
{
	t_seq 	*tmp_s;
	t_seq	*to_delete; 
	int		i;

	i = 0;
	while (i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		if (tmp_s == NULL)
			break; 
		while (tmp_s)
		{
			if (tmp_s->redir)
			{
				ft_free_redir(tmp_s->redir);
				ft_lstclear(&tmp_s->redir, free);	
			}
			if (tmp_s->word)
				ft_lstclear(&tmp_s->word, free);
			to_delete = tmp_s;
			tmp_s = tmp_s->next_pipe;
			free(to_delete); //pas sure 
		}
		i++;
	}
	//free(tab_seq); //pas sure
}

void ft_free_command(t_list *cmd_list)
{	
	t_list			*tmp;
	t_simple_cmd	*cmd;

	tmp = cmd_list;
	while (tmp)
	{
		cmd = (t_simple_cmd *)tmp->content;
		if (cmd->job)
			free(cmd->job);
		if (cmd->av)
			free_double_tab(cmd->av);
		tmp = tmp->next;
	}
}

