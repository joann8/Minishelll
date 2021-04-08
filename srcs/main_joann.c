/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_joann.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/08 14:54:38 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int main(int ac, char **av)
{
	t_list	*token_list;
	t_seq	*tab_seq;
	char	*line;
	tab_seq = NULL;

	(void)ac;
	(void)av;
	token_list = NULL;
	while (get_next_line(0, &line) > 0)
	{
		token_list = ft_get_token_list(token_list, line);
		if (token_list == NULL)
		{
			printf("pbm tokenize\n");
			return (0);
		}
		//printf("\n*** FIRST AFTER FUNCTION ***\n");
		//print_token(token_list);
		assign_type_1(token_list);
	//	printf("\n*** AFTER ASSIGN 1 ***\n");
		//print_token(token_list);
		if (assign_type_2(token_list) == -1)
			return(printf("wrong inputs\n"));
		printf("\n*** AFTER ASSIGN 2 ***\n");
		print_token(token_list);
		free(line);
	}
	free(line);
	create_sequence(tab_seq, token_list);
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
