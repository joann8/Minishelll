/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:40 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 16:27:53 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		p_error(int errnum, char *error, int ret_wanted)
{
	(void)errnum;

	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	return (ret_wanted);
}

int		print_syntax_error(int errnum, char *error, int ret_wanted)
{
	(void)errnum;

	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd("erreur de syntaxe près du symbole inattendu « ",
		STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(" »\n", STDERR_FILENO);
	return (ret_wanted);
}

int		print_err(char *str1, char *str2, char *str3, int ret_wanted)
{
	if (str1)
		ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
		ft_putstr_fd(str2, STDERR_FILENO);
	if (str3)
		ft_putstr_fd(str3, STDERR_FILENO);
	return (ret_wanted);
}

/*
int		add_err_lst(char *str1, char *str2, char *str3)
{
	t_list *s1;
	t_list *s2;
	t_list *s3;

	if (str1)
	{
		if ((s1 = ft_lstnew(ft_strdup(str1))) == NULL)
			return (-1);
		ft_lstadd_back(s1);
	}
	if (str2)
	{
		if ((s2 = ft_lstnew(ft_strdup(str2))) == NULL)
			return (-1);
		ft_lstadd_back(s2);
	}
	if (str3)
	{
		if ((s3 = ft_lstnew(ft_strdup(str3))) == NULL)
			return (-1);
		ft_lstadd_back(s3);
	}
	return (0);
}
*/
/*
int		print_cmd_error(int errnum, t_list *l)
{
	t_list *tmp;

	(void)errnum;
	tmp = l;
	while (tmp)
	{
		ft_putstr_fd((char*)(tmp->content), STDERR_FILENO);
		tmp = tmp->next;
	}
	return (-1);
}
*/
