/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:00:18 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 19:56:38 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_free(void *content, int wished_return)
{
	free(content);
	return (wished_return);
}

void	ft_free_token(t_list *token_list)
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

void	ft_free_redir(t_list *redir_list)
{
	t_list		*tmp;
	t_redir		*red;

	tmp = redir_list;
	while (tmp)
	{
		red = (t_redir*)(tmp->content);
		printf("res->filname = %s\n", red->file_name);
		free(red->file_name);
		tmp = tmp->next;
	}
}

void	ft_free_tab_seq_help(t_seq *tmp_s)
{
	int		j;
	t_seq	*to_delete;
	t_list	*r_node;
	t_list	*r_tmp;
	t_redir	*adri;

	j = 0;
	while (tmp_s)
	{
		if (tmp_s->redir)
		{
			//ft_free_redir(tmp_s->redir);
			//ft_lstclear(&(tmp_s->redir), free);
			r_node = (t_list *)tmp_s->redir;
			r_tmp = r_node;
			while (r_node)
			{
				adri = (t_redir *)r_node->content;
				free(adri->file_name);
				r_node = r_node->next;
			}
			ft_lstclear(&r_tmp, free);
		}
		if (tmp_s->word)
			ft_lstclear(&(tmp_s->word), free);
		to_delete = tmp_s;
		tmp_s = tmp_s->next_pipe;
		if (j > 0)
			free(to_delete);
		j++;
	}
}

void	ft_free_tab_seq(t_seq *tab_seq, int seq_nb)
{
	t_seq	*tmp_s;
	int		i;

	i = 0;
	while (i < seq_nb)
	{
		tmp_s = tab_seq + i;
		ft_free_tab_seq_help(tmp_s);
		i++;
	}
	free(tab_seq);
}
