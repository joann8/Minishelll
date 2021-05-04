/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:56:23 by calao             #+#    #+#             */
/*   Updated: 2021/05/04 13:40:12 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_print_str_table(char **av)
{
	while (*av)
	{
		ft_putstr(*av);
		ft_putchar('\n');
		av++;
	}
}

void	ft_print_envtlst_fd(t_list *env_head, int fd)
{
	t_var	*var;
	t_list	*tmp;

	tmp = env_head;
	while (tmp)
	{
		var = (t_var*)(tmp->content);
		if (var->on == 1)
		{
			write(fd, var->name, ft_strlen(var->name));
			write(fd, "=", 1);
			write(fd, var->value, ft_strlen(var->value));
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void	ft_print_exportlst_fd(t_list *env_head, int fd)
{
	t_var	*var;
	t_list	*tmp;

	tmp = env_head;
	while (tmp)
	{
		var = (t_var*)(tmp->content);
		write(fd, "declare -x ", 11);
		write(fd, var->name, ft_strlen(var->name));
		write(fd, "=\"", 2);
		write(fd, var->value, ft_strlen(var->value));
		write(fd, "\"\n", 2);
		tmp = tmp->next;
	}
}
