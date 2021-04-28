/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/28 15:38:33 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		manage_tokenize(t_list **token_list, char *line)
{
	int res;

	res = ft_get_token_list(token_list, line);
	if (res != 0)
	{
		g.exit_status = 2;
		ft_free_token(*token_list);
		ft_lstclear(token_list, free);
		return (res);
	}
	assign_type_1(*token_list);
	if (assign_type_2(*token_list) == 1)
	{
		ft_free_token(*token_list);
		ft_lstclear(token_list, free);
		g.exit_status = 2;
		return (1);
	}
//	printf("\n****RESUlT TOKEN******\n");
//	print_token(*token_list);
	return (0);
}

void	ft_clear_before_quit(t_list **token_list, t_seq **tab_seq,
			t_list **cmd_list, int seq_nb)
{
	if (token_list && *token_list)
	{
		ft_free_token(*token_list);
		ft_lstclear(token_list, free);
	}
	if (tab_seq && *tab_seq)
		ft_free_tab_seq(*tab_seq, seq_nb);
	if (cmd_list && *cmd_list)
	{
		ft_free_command(*cmd_list);
		ft_lstclear(cmd_list, free);
	}
}

int		execution_main(char *line, t_list **var_list)
{
	t_list			*token_list;
	t_seq			*tab_seq;
	//t_list			*cmd_list;
	int				seq_nb;
	int				res;

	tab_seq = NULL;
//	cmd_list = NULL;
	token_list = NULL;
	//
	/*
	write(1, "\ninput = [", 10);
	write(1, line, ft_strlen(line));
	write(1, "]\n", 2);
	*/
	//
	res = manage_tokenize(&token_list, line);
	if (res != 0)
		return (res);
	seq_nb = get_seq_number(token_list);
	tab_seq = create_sequence(tab_seq, token_list, seq_nb);
	if (tab_seq == NULL)//seules erreurs possibles == malloc
	{
		ft_clear_before_quit(&token_list, &tab_seq, NULL, seq_nb);
		return (-1);
	}
	///gestion erreur ok jusque ici
	//
	/*
	printf("\n****RESUlT SEQUENCE******\n");
	print_seq(tab_seq, seq_nb);
	printf("\n**********\n");
	*/
	//
	res = create_command(tab_seq, seq_nb, var_list);
	//res = 0 tout est ok
	//res = 1 : erreur exec command mais on prend le next input
	//res = -1 : erreur malloc ou autre hors exe (pipe), on arrete le pgm
	// 19 exit
	ft_clear_before_quit(&token_list, &tab_seq, NULL, seq_nb); //pbm tab seq

	//printf("\n**********\n");
	return (res);
}
