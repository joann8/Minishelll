/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/26 10:53:04 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	print_list(t_list *list)
{
	t_list	*tmp;
	int		tour;
	
	tour= 0;
	tmp = list;
	while (tmp)
	 {
		printf("%d.list->content = %s\n", tour, (char *)tmp->content);
		tmp = tmp->next;
		tour++;
	}
}

void	print_token(t_list *token)
{
	t_list	*tmp;
	t_token	*tmp2;
	int		tour;
	
	tour= 0;
	tmp = token;
	while (tmp)
	 {
		tmp2 = (t_token *)tmp->content;
		printf("%d.token->e_type = %d\n  token->tok_str=%s\n", tour, (t_e_type)(tmp2->e_type), tmp2->tok_str);
		tmp = tmp->next;
		tour++;
	}
}

void	print_redir(t_list *redir)
{
	t_list	*tmp;
	t_redir	*tmp2;
	int		tour;
	
	tour= 0;
	tmp = redir;
	while (tmp)
	 {
		tmp2 = (t_redir *)tmp->content;
		printf("%d.redir->e_type = %d\n  redir->file_name=%s\n", tour, tmp2->e_type, tmp2->file_name);
		tmp = tmp->next;
		tour++;
	}
}

void	print_cmd_piped(t_simple_cmd *cmd_list)
{
	t_simple_cmd	*tmp_c;
	int				i;
	int				j;

	i = 0;
	tmp_c = cmd_list;
	while (tmp_c)
	{
		printf("**** CMD %d*****\n", i);
		printf("job = %s\n", tmp_c->job);
		j = 0;
		while (j < tmp_c->ac)
		{
			if (tmp_c->av)
			{
				printf("av[%d] = %s\n", j, tmp_c->av[j]);
				j++;
			}
			else
				break;
		}
		printf("ac = %d\n", tmp_c->ac);
		printf("fd_in = %d\n", tmp_c->fd_in);
		printf("fd_out = %d\n", tmp_c->fd_out);
		printf("pipe mod: %d\n", tmp_c->pipe_mod);
		printf("pipe pos: %d\n", tmp_c->pipe_pos);
		printf("on: %d\n", tmp_c->on);
		printf("pipe p.fd_out_to_use : %d\n", tmp_c->p.fd_out_to_use);
		printf("pipe p.fd_in_to_use : %d\n", tmp_c->p.fd_in_to_use);
		tmp_c = tmp_c->next_pipe;
		i++;
	}
}

void	print_cmd(t_list *cmd_list)
{
	t_list			*tmp_l;
	t_simple_cmd	*tmp_c;
	int				i;
	int				j;

	i = 0;
	tmp_l = cmd_list;
	while (tmp_l)
	{
		tmp_c = (t_simple_cmd *)tmp_l->content;
		printf("**** CMD %d*****\n", i);
		printf("job = %s\n", tmp_c->job);
		j = 0;
		while (j < tmp_c->ac)
		{
			if (tmp_c->av)
			{
				printf("av[%d] = %s\n", j, tmp_c->av[j]);
				j++;
			}
			else
				break;
		}
		printf("ac = %d\n", tmp_c->ac);
		printf("fd_in = %d\n", tmp_c->fd_in);
		printf("fd_out = %d\n", tmp_c->fd_out);
		printf("pipe mod: %d\n", tmp_c->pipe_mod);
		printf("pipe pos: %d\n", tmp_c->pipe_pos);
		//printf("retour : %d\n", tmp_c->retour);
		tmp_l = tmp_l->next;
		i++;
	}
}

void	print_seq(t_seq *tab_seq, int seq_nb)
{
	t_seq *tmp;
	int i;
	int pipe;
	i = 0;

	while (i < seq_nb)
	{
		printf("--SEQUENCE %d\n", i);
		tmp = &(tab_seq[i]);
		pipe = 0;
		while (tmp)
		{
			printf("----PIPE %d\n", pipe);
			printf("tab_seq[%d].pipe_pos = %d\n", i, tmp->pipe_pos);
			printf("tab_seq[%d].pipe_total = %d\n", i, tmp->pipe_total);
			printf("tab_seq[%d].words:\n", i);
			if (tmp->word)
				print_list(tmp->word);
			printf("tab_seq[%d].redir:\n", i);
		//	printf("here\n");
		//	printf("tmp->redir = %p\n", tmp->redir);
			if (tmp->redir)
			{
		//		printf("there\n");
				print_redir(tmp->redir);
			}
			printf("\n");
		//	printf("here again\n");
			tmp = tmp->next_pipe;
			pipe++;
		}
		i++;
	}
}

