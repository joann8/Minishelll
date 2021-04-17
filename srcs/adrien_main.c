/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adrien_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/17 13:41:21 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


char	*ft_relative_to_absolute(char *exec);
int		ft_path_is_relative(char *str);

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

int		ft_update_pwd(t_list *pwd_node, char *cwd)
{
//	t_var *var;

	free(((t_var *)(pwd_node->content))->value);
	if ((((t_var *)(pwd_node->content))->value = ft_strdup(cwd)) == NULL)
		return (-1);
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list	*env_lst;
	char *user_input;
	char *prompt;
	char *tmp;
	char *log_path;


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
