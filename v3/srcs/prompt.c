/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/05/03 23:04:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*truncate_pwd(char *pwd, t_list **env_lst)
{
	int		i;
	t_list	*home;
	t_var	*tmp;

	i = ft_strlen(pwd) - 1;
	while (i > 0 && pwd[i] != '/')
		i--;
	home = ft_lstfind_env(env_lst, "HOME", ft_strcmp);
	if (home != NULL)
	{
		tmp = (t_var *)home->content;
		if (tmp->on == 1 && ft_strcmp(pwd, tmp->value) == 0)
			return (ft_strdup("~"));
	}
	if (ft_strcmp(pwd, "/") == 0)
		return (ft_strdup("/"));
	if (pwd[i] == '/')
		return (ft_strdup(pwd + i + 1));
	else
		return (ft_strdup(pwd + i));
}

char	*ft_make_prompt(t_list **env_lst)
{
	t_list	*pwd_node;
	char	*tmp;
	char	*pwd;
	char	*prompt;

	pwd_node = (ft_lstfind_env(env_lst, "PWD", ft_strcmp));
	if (pwd_node == NULL)
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(((t_var *)(pwd_node->content))->value);
	if (pwd == NULL)
		return (NULL);
	tmp = pwd;
	pwd = truncate_pwd(pwd, env_lst);
	free(tmp);
	if (pwd == NULL)
		return (NULL);
	prompt = ft_strjoin("msh@jacher-adconsta:", pwd);
	free(pwd);
	if (prompt == NULL)
		return (NULL);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "$ ");
	free(tmp);
	return (prompt);
}

void	ft_print_prompt(t_term *term, char *prompt)
{
	int i;
	int color;

	i = 0;
	color = 1;
	while (prompt[i])
	{
		if (prompt[i] == '$' && prompt[i + 2] == '\0')
			tputs(ANSI_WHITE, 1, ft_termcap_on);
		else if (color == 1 && prompt[i] == ':')
		{
			tputs(ANSI_WHITE, 1, ft_termcap_on);
			color = 2;
		}
		else if (color == 1)
			tputs(ANSI_BOLD_RED, 1, ft_termcap_on);
		else if (color == 2)
			tputs(ANSI_BOLD_YELLOW, 1, ft_termcap_on);
		ft_putchar(prompt[i]);
		i++;
		tputs(term->me, 1, ft_termcap_on);
	}
}
