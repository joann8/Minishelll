/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 13:11:22 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			assign_list_redir_2(t_redir *r, t_simple_cmd *cmd)
{
	if (r->e_type == IN)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);//Besoin d'essayer de READ ? QUID si c'est un dossier ?
		cmd->fd_in = open(r->file_name, O_RDONLY);
		if (cmd->fd_in < 0)//Erreur file not found to print
			return (-1);
	}
	else if (r->e_type == OUT)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);//Besoin d'essayer de READ ? QUID si c'est un dossier ?
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);//664 a checker
		if (cmd->fd_out < 0)//error opening with wrong rights or opening DIR
			return (-1);//Erreur file not found to print
	}
	else if (r->e_type == APPEND)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);//Besoin d'essayer de READ ? QUID si c'est un dossier ?
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (cmd->fd_out < 0)
			return (-1);//Erreur file not found to print
	}
	return (0);
}

int			assign_list_redir(t_seq *seq, t_simple_cmd *cmd)
{
	t_list	*tmp_l;
	t_redir	*tmp_r;

	tmp_l = seq->redir;
	while (tmp_l)
	{
		tmp_r = (t_redir *)tmp_l->content;
		if (assign_list_redir_2(tmp_r, cmd) == -1)
			return (-1);
		tmp_l = tmp_l->next;
	}
	return (0);
}

int			assign_list_word(t_seq *seq, t_simple_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	cmd->ac = ft_lstsize(seq->word);
	cmd->av = malloc(sizeof(char*) * (cmd->ac + 1));
	if (cmd->av == NULL)
		return (-1);//erreur malloc
	tmp = seq->word;
	i = 0;
	while (tmp)
	{
		if (i == 0)//error opening with wrong rights
		{
			cmd->job = ft_strdup((char *)tmp->content);
			if (cmd->job == NULL)
				return (-1);//erreur malloc
		}
		cmd->av[i] = ft_strdup(tmp->content);
		if (cmd->job == NULL)//erreur malloc
			return (-1);
		tmp = tmp->next;
		i++;
	}
	cmd->av[i] = NULL;
	return (0);
}

void		assign_pipes(t_seq *seq, t_simple_cmd *cmd)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (seq->pipe_total > 0)
		cmd->pipe_mod = 1;
	else
		cmd->pipe_mod = 0;
	if (seq->pipe_pos == seq->pipe_total)
		cmd->pipe_pos = 1;
	else if (seq->pipe_pos == 0)
		cmd->pipe_pos = -1;
	else
		cmd->pipe_pos = 0;
}

t_list		*create_command(t_list *cmd_list, t_seq *tab_seq, int seq_nb, t_list **env)
{
	int				i;
	t_seq			*tmp_s;
	t_simple_cmd	*tmp_c;

	i = 0;
	while (i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		make_expansion_cmd_by_cmd(tmp_s, env);
		while (tmp_s)
		{
			tmp_c = malloc(sizeof(t_simple_cmd));
			if (tmp_c == NULL)
				return (NULL);
			if (assign_list_word(tmp_s, tmp_c) == -1)
				return (NULL); //erreur malloc
			assign_pipes(tmp_s, tmp_c);
			if (assign_list_redir(tmp_s, tmp_c) == -2)
				return (NULL); //erreur malloc
			ft_lstadd_back(&cmd_list, ft_lstnew((void*)tmp_c));
			tmp_s = tmp_s->next_pipe;
		}
		printf("EXECUTE %s\n", tmp_c->job);
		execute_cmd_by_cmd(tmp_c, env);
		i++;
	}
	return (cmd_list);
}
