/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/19 15:13:11 by jacher           ###   ########.fr       */
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

	g_process.exit_status = 0;

	//Creation de la lst de env_var;	
	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	if (env_lst == NULL)
		return (-1);
	
	// Creation chemin absolu vers le fichier d'historique
	log_path = ft_my_getcwd();
	if (log_path == NULL)
	{
		ft_lstclear_envlst(&env_lst);
		return (-1);
	}
	tmp = log_path;
	log_path = ft_strjoin(log_path, "minishell.log");
	free(tmp);

	while (1)
	{
		prompt = ft_make_prompt(&env_lst);
		if (prompt == NULL)
		{
			ft_lstclear_envlst(&env_lst);
			free(log_path);
			return (-1);
		}
		ft_get_userinput(&user_input, prompt, log_path);
		if (user_input == NULL)
		{	
			free(prompt);
			ft_lstclear_envlst(&env_lst);
			free(log_path);
			return (-1);
		}
		if (ft_strcmp(user_input, "") != 0)
			execution_main(user_input, &env_lst); 
		free(prompt);
		free(user_input);
	}
	ft_lstclear_envlst(&env_lst);
	free(log_path);
	return (0);
}
