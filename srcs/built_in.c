/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 09:56:25 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_env(t_list **env);

int		find_built_in(t_simple_cmd *cmd, t_pipe *p, t_list **error, t_list **env)
{
	(void)error;
	(void)env;
	if (ft_strcmp(cmd->job, "echo") == 0)
	{
		printf("ECHO FOUND!\n");
		return(ft_echo(cmd, p));
	}
	if (ft_strcmp(cmd->job, "env") == 0)//ADRIEN
	{
		write(1, "adrien_env\n", 11);
		ft_env(env);
		return (6);
	}
	if (ft_strcmp(cmd->job, "pwd") == 0)//JOANN
		return (ft_pwd(cmd, p, error, env));

	//	if (ft_strcmp(cmd->job, "cd") == 0)//ADRIEN
//		return (2);
	//-1 retourne si erreur malloc
/*	if (ft_strcmp(cmd->job, "export") == 0)//ADRIEN
		return (4);
	if (ft_strcmp(cmd->job, "unset") == 0)//ADRIEN
		return (5);
*/
	
	if (ft_strcmp(cmd->job, "exit") == 0)//JOANN
		return (7);
	return (0);
}

void	ft_env(t_list **env)
{
	t_list	*tmp;
	t_var	*var;

	tmp = *env;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (var->on == 1)
		{
			ft_putstr(var->name);
			ft_putstr("=");
			ft_putstr(var->value);
			ft_putstr("\n");
		}
		tmp = tmp->next;
	}
}

