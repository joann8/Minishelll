/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/08 19:15:35 by jacher           ###   ########.fr       */
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
		printf("%d.token->e_type = %d\n  token->tok_str=%s\n", tour, tmp2->e_type, tmp2->tok_str);
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

