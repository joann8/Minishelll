/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/19 15:01:41 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_make_prompt(t_list **env_lst)
{
	t_list	*pwd_node;
	char *tmp;
	char *pwd;
	char *prompt;


	pwd_node = (ft_lstfind_env(env_lst, "PWD", ft_strcmp));
	if (pwd_node == NULL)
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(((t_var *)(pwd_node->content))->value);
	if (pwd == NULL)
		return (NULL);
	prompt = ft_strjoin("minishell@jacher-adconsta:", pwd);
	free(pwd);
	if (prompt == NULL)
		return (NULL);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "$ ");
	free(tmp);
	if (prompt == NULL)
		return (NULL);
	return (prompt);
}
