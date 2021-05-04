/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:58:35 by calao             #+#    #+#             */
/*   Updated: 2021/05/04 13:57:31 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_check_export_name(char *str)
{
	int i;

	i = -1;
	if (ft_isalpha(str[0]) || str[0] == '_')
		i++;
	else
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		else if (i > 0 && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		else
			return (0);
	}
	return (1);
}

int		ft_export_replace_value(t_list *exist, char *str)
{
	t_var	*v_tmp;
	char	*new;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (1);
	i++;
	new = ft_strdup(str + i);
	if (new == NULL)
		return (-1);
	v_tmp = (t_var *)exist->content;
	v_tmp->on = 1;
	free(v_tmp->value);
	v_tmp->value = new;
	return (1);
}

int		ft_export_print(t_list **env, int fd_out)
{
	t_list *copy;

	copy = NULL;
	if (ft_lst_env_copy(&copy, env) == -1)
		return (-1);
	ft_lst_env_sort(&copy, ft_strcmp);
	ft_print_exportlst_fd(copy, fd_out);
	ft_lstclear_envlst(&copy);
	return (0);
}

int		ft_export_second_part(char *str, t_list **env)
{
	t_list	*exist;
	char	*key;
	int		ret;

	if ((key = ft_getenv_name(str)) == NULL)
		return (-1);
	if ((exist = ft_lstfind_export(env, key, ft_strcmp)))
		ret = ft_export_replace_value(exist, str);
	else
		ret = ft_lst_env_addback(env, str);
	free(key);
	if (ret == -1)
		return (-1);
	return (0);
}

int		ft_export(t_list **env, t_simple_cmd *cmd, int fd_out)
{
	int		res;
	int		i;
	int		count;

	i = 1;
	res = 0;
	count = 0;
	while (i < cmd->ac)
	{
		if (cmd->av[i] != NULL && ft_check_export_name(cmd->av[i]) == 0)
		{
			res = 1;
			print_err("msh: export: `", cmd->av[i],
					"': not a valid identifier\n", 1);
		}
		else if (cmd->av[i] != NULL
				&& ft_export_second_part(cmd->av[i], env) == -1)
			return (-1);
		else if (cmd->av[i] == NULL)
			count++;
		i++;
	}
	if (count == cmd->ac - 1)
		return (ft_export_print(env, fd_out));
	return (res);
}
