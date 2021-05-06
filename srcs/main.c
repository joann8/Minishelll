/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/05/04 10:47:10 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		main_free(t_list **env_lst, char *s1, char *s2, int ret_wanted)
{
	if (env_lst && *env_lst)
		ft_lstclear_envlst(env_lst);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ret_wanted);
}

int		main_loop(t_list **env_lst, char *log_path, int ret)
{
	char *prompt;
	char *user_input;

	prompt = ft_make_prompt(env_lst);
	if (prompt == NULL)
		return (main_free(env_lst, log_path, NULL, -1));
	listen_signals('r');
	if (ft_get_userinput(&user_input, prompt, log_path, &ret) == -1)
		return (main_free(env_lst, log_path, prompt, -1));
	if (user_input != NULL && ft_strcmp(user_input, "") != 0
			&& !ft_is_only_space(user_input))
	{
		listen_signals('e');
		if (execution_main(user_input, env_lst) == 227)
			ret = -227;
	}
	return (main_free(NULL, user_input, prompt, ret));
}

int		main(int ac, char **av, char **envp)
{
	t_list	*env_lst;
	char	*tmp;
	char	*log_path;
	int		ret;

	(void)ac;
	(void)av;
	g_msh.exit_status = 0;
	ret = 0;
	env_lst = NULL;
	if (ft_make_envlst(&env_lst, envp) == -1)
		return (main_free(&env_lst, NULL, NULL, 1));
	log_path = getcwd(NULL, 0);
	if (log_path == NULL)
		return (main_free(&env_lst, NULL, NULL, 1));
	tmp = log_path;
	log_path = ft_strjoin(log_path, "/minishell.log");
	free(tmp);
	if (log_path == NULL)
		return (main_free(&env_lst, NULL, NULL, 1));
	while (ret != -227)
		if ((ret = main_loop(&env_lst, log_path, ret)) == -1)
			return (1);
	return (main_free(&env_lst, log_path, NULL, g_msh.exit_status));
}
