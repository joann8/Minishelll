/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/12 11:29:13 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int main(int ac, char **av, char **envp)
{
	t_list			*token_list;
	t_seq			*tab_seq;
	t_list			*cmd_list;
	char			*line;
	t_list			*var_list;
	
	(void)ac;
	(void)av;
	tab_seq = NULL;
	cmd_list = NULL;
	token_list = NULL;
	var_list = NULL;
	ft_make_envlst(&var_list, envp);
//	ft_print_envlst(var_list);
	ft_get_userinput(&line);
	token_list = ft_get_token_list(token_list, line);
	if (token_list == NULL)
	{
		printf("pbm tokenize\n");
		return (0);
	}
	printf("\n*** FIRST AFTER FUNCTION ***\n");
	print_token(token_list);
	assign_type_1(token_list);
//	printf("\n*** AFTER ASSIGN 1 ***\n");
	//print_token(token_list);
	if (assign_type_2(token_list) == -1)
		return(printf("wrong inputs\n"));
//	printf("\n*** AFTER ASSIGN 2 ***\n");
//	print_token(token_list);
	free(line);

	int seq_nb;
	seq_nb = get_seq_number(token_list);
	tab_seq = create_sequence(tab_seq, token_list, seq_nb);
//	print_seq(tab_seq, seq_nb);
	printf("\n******\n");
	tab_seq = make_expansion(tab_seq, seq_nb, var_list);
	print_seq(tab_seq, seq_nb);
//	cmd_list = create_command(cmd_list, tab_seq, seq_nb);
	ft_lstclear_envlst(&var_list);
	return (0);
}

/*

int main(int ac, char **av)
{
	char	*line;

	(void)ac;
	(void)av;
	while (get_next_line(0, &line) > 0)
	{
		printf("line = %s\n", line);
	}
	return (0);
}
	
*/
