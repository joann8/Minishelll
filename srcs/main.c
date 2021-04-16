/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 17:51:57 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int tmp_main(char *line, t_list **var_list)//a changer nous emem tab env
{
	t_list			*token_list;
	t_seq			*tab_seq;
	t_list			*cmd_list;
	int				seq_nb;
	
	tab_seq = NULL;
	cmd_list = NULL;
	token_list = NULL;
	write(1, "\ninput = [", 10);
	write(1, line, ft_strlen(line));
	write(1, "]\n", 2);
	
	if (ft_get_token_list(&token_list, line) == -1)
	{
		ft_free_token(token_list);
		ft_lstclear(&token_list, free);
		printf("pbm tokenize\n");
		return (0);
	}
	assign_type_1(token_list);
	if (assign_type_2(token_list) == -1)
	{
		ft_free_token(token_list);
		ft_lstclear(&token_list, free);
		return(printf("wrong inputs\n"));
	}
	printf("\n****RESUlT TOKEN******\n");
	print_token(token_list);

	seq_nb = get_seq_number(token_list);
	tab_seq = create_sequence(tab_seq, token_list, seq_nb);
	if (tab_seq ==  NULL)
	{
		ft_free_token(token_list);
		ft_lstclear(&token_list, free);
		return(printf("pbm table sequence\n"));
	}
	tab_seq = make_expansion(tab_seq, seq_nb, *var_list);
	if (tab_seq ==  NULL)
	{
		ft_free_token(token_list);
		ft_lstclear(&token_list, free);
		return(printf("pbm table sequence\n"));
	}
	printf("\n****RESUlT SEQUENCE******\n");
	print_seq(tab_seq, seq_nb);
	cmd_list = create_command(cmd_list, tab_seq, seq_nb);
	printf("\n****RESUlT COMMAND******\n");
	if (cmd_list == NULL)
	{
		ft_free_token(token_list);
		ft_lstclear(&token_list, free);
		ft_free_tab_seq(tab_seq, seq_nb);
		return(printf("pbm table sequence\n"));
	}
	print_cmd(cmd_list);
	printf("\n****START EXECUTE COMMAND******\n\n");
	execute_cmd(cmd_list, var_list);
	ft_free_token(token_list);
	ft_lstclear(&token_list, free);
	ft_free_tab_seq(tab_seq, seq_nb);
	ft_free_command(cmd_list);
	ft_lstclear(&cmd_list, free);
	return (0);
}
