/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:40 by jacher            #+#    #+#             */
/*   Updated: 2021/05/01 18:46:50 by jacher           ###   ########.fr       */
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

int		print_syntax_error(int ret_wanted)
{
	ft_putstr_fd("msh: syntax error\n", STDERR_FILENO);
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

int		print_err_pipe(char *str1, char *str2, char *str3, int ret_wanted)
{
	char *new1;
	char *new2;

	new1 = NULL;
	if (str1 && str2)
	{
		if ((new1 = ft_strjoin(str1, str2)) == NULL)
			return (-1);
		if (str3)
		{
			new2 = new1;
			if ((new1 = ft_strjoin(new2, str3)) == NULL)
			{
				free(new2);
				return (-1);
			}
			free(new2);
		}
	}
	if (new1)
	{
		ft_putstr_fd(new1, STDERR_FILENO);
		free(new1);
	}
	return (ret_wanted);
}
