/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:40 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 11:56:12 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	print_str(char *str)
{
	// pour le prompt : "$ " ou "> "
	write(1, str, ft_strlen(str));
}

int		print_error(int errnum, char *error, int ret_wanted)//errno?
{
	(void)errnum;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);//affiche l'erreur dans le std err
	return (ret_wanted);
}

int		print_syntax_error(int errnum, char *error, int ret_wanted)//errno?
{
	(void)errnum;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("erreur de syntaxe près du symbole inattendu « ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(" »\n", STDERR_FILENO);
	return (ret_wanted);
}

void	ft_add_error_list(t_list **error, char *s1, char *s2, char *s3)
{
	if (s1)
		ft_lstadd_back(error, ft_lstnew(ft_strdup(s1)));
	if (s2)
		ft_lstadd_back(error, ft_lstnew(ft_strdup(s2)));
	if (s3)
		ft_lstadd_back(error, ft_lstnew(ft_strdup(s3)));
}
	

int		print_cmd_error(int errnum, t_list *l)//erno?
{
	t_list *tmp;

	(void)errnum;
	tmp = l;
	while (tmp)
	{
		ft_putstr_fd((char*)(tmp->content), STDERR_FILENO);//affiche l'erreur dans le std err
	//	ft_putstr_fd(" : commande introuvable\n", STDERR_FILENO);
		tmp = tmp->next;	
	}
	return (-1);
}

/*
int		print_arg_error(int errnum, t_list *l)//erno?
{
	t_list *tmp;

	(void)errnum;
	tmp = l;
	while (tmp)
	{
		ft_putstr_fd((char*)(tmp->content), STDERR_FILENO);//affiche l'erreur dans le std err
		//ft_putstr_fd(" : commande introuvable\n", STDERR_FILENO);
		ft_putstr_fd(" : ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		tmp = tmp->next;	
	}
	return (-1);
}*/

