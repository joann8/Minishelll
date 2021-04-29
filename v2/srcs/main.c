/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/29 12:03:14 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list	*env_lst;
	char *user_input;
	char *prompt;
	char *tmp;
	char *log_path;
	int	 ret;
	
	g.exit_status = 0;
	ret = 0;

	//Creation de la lst de env_var;	
	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	if (env_lst == NULL)
	{
		ft_lstclear_envlst(&env_lst);
		return (1);
	}
	// Creation chemin absolu vers le fichier d'historique. Si le chemin est diffenrent entre subminishell, nouvelle file creer.
	log_path = getcwd(NULL, 0);
	if (log_path == NULL)
	{
		ft_lstclear_envlst(&env_lst);
		return (1);
	}
	tmp = log_path;
	log_path = ft_strjoin(log_path, "/minishell.log");
	free(tmp);
	if (log_path == NULL)
	{
		ft_lstclear_envlst(&env_lst);
		return (1);
	}
	// existence d'un boleen pour free et gagner des lignes?
	while (ret != -227)
	{
		prompt = ft_make_prompt(&env_lst);
		if (prompt == NULL)
		{
			ft_lstclear_envlst(&env_lst);
			free(log_path);
			return (1);
		}
		signal(SIGINT, read_ctrl_c);
		signal(SIGQUIT, read_ctrl_quit);
		if (ft_get_userinput(&user_input,
					prompt, log_path, &ret) == -1) //diff du malloc vs ctrl-d
		{
			free(prompt);
			ft_lstclear_envlst(&env_lst);
			free(log_path);
			return (1);
		}
		if (user_input != NULL && ft_strcmp(user_input, "") != 0
				&& !ft_is_only_space(user_input))
		{
			signal(SIGINT, exec_ctrl_c);
			signal(SIGQUIT, exec_ctrl_quit);
			if (execution_main(user_input, &env_lst) == 227)
				ret = -227;
		}	
		free(prompt);
		free(user_input);
	}
	ft_lstclear_envlst(&env_lst);
	free(log_path);
	return (g.exit_status);
}
