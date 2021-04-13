/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:40 by jacher            #+#    #+#             */
/*   Updated: 2021/04/13 13:58:19 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	print_str(char *str)
{
	// pour le prompt : "$ " ou "> "
	write(1, str, ft_strlen(str));
}

int		print_error(int errnum, char *error)//errno?
{
	(void)errnum;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);//affiche l'erreur dans le std err
	return (-1);
}

int		print_syntax_error(int errnum, char *error)//errno?
{
	(void)errnum;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("erreur de syntaxe près du symbole inattendu « ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(" »\n", STDERR_FILENO);
	return (-1);
}
