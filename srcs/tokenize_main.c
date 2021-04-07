/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 17:02:06 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	print_list(t_list *lst)
{
	t_list *tmp;
	tmp = lst;
	int tour = 0;
	
	while (tmp)
	 {
		printf("%d.lst->content = %s\n", tour, tmp->content);
		tmp = tmp->next;
		tour++;
	}
}

int		ft_create_token(t_list **token_list, char *input, int start, int end)
{
	char *str;

	str = malloc(sizeof(char) * (end - start + 2));
	if (str == NULL)
		return (-1); //erreur malloc
	ft_strlcpy(str, input + start, end - start  + 2);
	ft_lstadd_back(token_list, ft_lstnew((void *)str));
	return (0);
}

t_list	*ft_get_token_list(t_list *token_list, char *input)
{
	int 	i;
	int		start;

	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]) > 0)
			i++;
		start = i;
		while (input[i] && is_whitespace(input[i]) == 0)
		{
			if (is_specific(input[i], 34) == 1)
				if (look_second_quote(34, input, &i) == -1)
					return (NULL); // erreur quote pas fermée;	
			if (is_specific(input[i], 39) == 1)
				if (look_second_quote(39, input, &i) == -1)
					return (NULL); // erreur quote pas fermée;
			i++;
		}
		if (i != start)
			if (ft_create_token(&token_list, input, start, i - 1) == -1)
				return (NULL); //erreur malloc
	}
	return (token_list);
}

int main(int ac, char **av)
{
	t_list	*token_list;

	(void)ac;
	token_list = NULL;
	token_list = ft_get_token_list(token_list,av[1]);
	if (token_list == NULL)
	{
		printf("pbm tokenize\n");
		return (0);
	}	
	print_list(token_list);
	return (0);
}
