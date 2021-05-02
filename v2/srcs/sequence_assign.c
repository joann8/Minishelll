/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:27:19 by jacher            #+#    #+#             */
/*   Updated: 2021/05/02 11:57:36 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		seq_assign_redir(t_seq *tmp, t_list *lst_tok, t_token *tok)
{
	t_redir *redir;
	t_list	*new;

	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		return (p_error(0, "malloc error\n", -1));
	redir->e_type = tok->e_type;
	lst_tok = lst_tok->next;
	redir->file_name = ft_strdup(((t_token*)(lst_tok->content))->tok_str);
	if (redir->file_name == NULL)
	{
		free(redir);
		return (p_error(0, "malloc error\n", -1));
	}
	new = ft_lstnew((void *)(redir));
	if (new == NULL)
	{
		free(redir->file_name);
		free(redir);
		return (p_error(0, "malloc error\n", -1));
	}
	ft_lstadd_back(&tmp->redir, new);
	return (0);
}

int		seq_assign_pipe(t_seq **tmp, int *pipe_pos)
{
	*pipe_pos += 1;
	(*tmp)->next_pipe = malloc(sizeof(t_seq));
	if ((*tmp)->next_pipe == NULL)
		return (p_error(0, "malloc error\n", -1));
	(*tmp) = (*tmp)->next_pipe;
	(*tmp)->pipe_pos = *pipe_pos;
	(*tmp)->word = NULL;
	(*tmp)->redir = NULL;
	(*tmp)->next_pipe = NULL;
	return (0);
}

int		seq_assign_word(t_seq **tmp, t_token *tok)
{
	t_list	*new;
	char	*tmp_c;

	tmp_c = ft_strdup(tok->tok_str);
	if (tmp_c == NULL)
		return (p_error(0, "malloc error\n", -1));
	new = ft_lstnew(tmp_c);
	if (new == NULL)
	{
		free(tmp_c);
		return (p_error(0, "malloc error\n", -1));
	}
	ft_lstadd_back(&(*tmp)->word, new);
	return (0);
}

int		seq_assign_sequence(t_seq **tmp, t_list **lst_tok, int *pipe_pos)
{
	t_token		*tok;

	tok = (t_token*)(*lst_tok)->content;
	if (tok->e_type == WORD)
	{
		if (seq_assign_word(tmp, tok) == -1)
			return (-1);
	}
	else if (tok->e_type == IN || tok->e_type == OUT || tok->e_type == APPEND)
	{
		if (seq_assign_redir(*tmp, *lst_tok, tok) == -1)
			return (-1);
	}
	else if (tok->e_type == PIPE)
	{
		if (seq_assign_pipe(tmp, pipe_pos) == -1)
			return (-1);
	}
	else if (tok->e_type == SEPARATOR)
	{
		*lst_tok = (*lst_tok)->next;
		return (1);
	}
	*lst_tok = (*lst_tok)->next;
	return (0);
}
