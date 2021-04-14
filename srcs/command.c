/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/14 19:10:10 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		init_pipe(int *pipe_link, t_seq *seq, t_simple_cmd *cmd)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;

	(void)pipe_link;
	if (seq->pipe_total > 0)
	{
		//Pas besoin de faire un pipe si derniere commande
		if (pipe(cmd->fd_tab) == -1)
			return (-1); // pipe error
	}
	return (0);
}
int		assign_list_redir(int *pipe_link, t_seq *seq, t_simple_cmd *cmd)
{
	t_list	*tmp_l;
	t_redir	*tmp_r;

	if (init_pipe(pipe_link, seq, cmd) == -1)
		return (-2);
	tmp_l = seq->redir;
	while (tmp_l)
	{
		tmp_r = (t_redir *)tmp_l->content;
		if (tmp_r->e_type == IN)
		{
			//est-ce qu'on peut fermer le stdin ??
			if (cmd->fd_in > 0)
				close(cmd->fd_in);
			//Besoin d'essayer de READ ? QUID si c'est un dossier ?
			cmd->fd_in = open(tmp_r->file_name, O_RDONLY);
			if (cmd->fd_in < 0)
			{
				//Erreur file not found to print
				return (-1);
			}
		}
		else if (tmp_r->e_type == OUT)
		{
			if (cmd->fd_out > 1)
				close(cmd->fd_out);
			printf("fd out = %d\n", cmd->fd_out);
			cmd->fd_out = open(tmp_r->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			printf("fd out = %d\n", cmd->fd_out);
			if (cmd->fd_out < 0)
			{
				//error opening with wrong rights or opening DIR
				return (-1);
			}
		}
		else if (tmp_r->e_type == APPEND)
		{
			if (cmd->fd_out > 1)
				close(cmd->fd_out);
			cmd->fd_out = open(tmp_r->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (cmd->fd_out < 0)
			{
				return (-1);
			}
		}
		tmp_l = tmp_l->next;
	}
	if (seq->pipe_pos !=  seq->pipe_total
			&& cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = cmd->fd_tab[1];
	if (seq->pipe_pos != 0
			&& cmd->fd_in == STDIN_FILENO)
		cmd->fd_in = *pipe_link;
	*pipe_link = cmd->fd_tab[0];
	return (0);
}

int		assign_list_word(t_seq *seq, t_simple_cmd *cmd)
{
	int		i;
	t_list	*tmp;
	int		size_arg;
	
	size_arg = ft_lstsize(seq->word);
	cmd->ac = size_arg;;
	cmd->av = malloc(sizeof(char*) * (size_arg + 1));
	if (cmd->av == NULL)
		return (-1); //erreur malloc
	tmp = seq->word;
	i = 0;
	while (tmp)
	{
		if (i == 0)
				//error opening with wrong rights
		{
			cmd->job = ft_strdup((char *)tmp->content);	
			if (cmd->job == NULL)
				return (-1); //erreur malloc
		}
		cmd->av[i] = ft_strdup(tmp->content);
		if (cmd->job == NULL) //erreur malloc
			return (-1);
		tmp = tmp->next;
		i++;
	}
	cmd->av[i] = NULL;
	return (0);
}

t_list *create_command(t_list *cmd_list, t_seq *tab_seq, int seq_nb)
{
	int				i;
	int				j;
	t_seq			*tmp_s;
	t_simple_cmd	*tmp_c;
	int				pipe_link;

	i = 0;
	j = 0;
	while (i < seq_nb)
	{
		pipe_link = -1;
		tmp_s = &tab_seq[i];
	//	printf("%d\n", i);
		while (tmp_s)
		{
			tmp_c = malloc(sizeof(t_simple_cmd));
			if (tmp_c == NULL)
				return (NULL);
			if (assign_list_word(tmp_s, tmp_c) == -1)
				return (NULL); //erreur malloc
			if (assign_list_redir(&pipe_link, tmp_s, tmp_c) == -2)
				return (NULL); //erreur malloc
			ft_lstadd_back(&cmd_list, ft_lstnew((void*)tmp_c));
			if (tmp_s->pipe_pos ==  tmp_s->pipe_total)
				tmp_c->last = 1;
			else
				tmp_c->last = 0;
			tmp_s = tmp_s->next_pipe;
		}
		i++;
	}
	return (cmd_list);
}
