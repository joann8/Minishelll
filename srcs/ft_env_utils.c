/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:42 by calao             #+#    #+#             */
/*   Updated: 2021/04/16 18:29:56 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int		ft_lst_onenv_size(t_list **env)
{
	t_list	*node;
	t_var	*var;
	int		i;

	i = 0;
	node = *env;
	while (node)
	{
		var = (t_var *)(node->content);
		if (var->on)
			i++;
		node = node->next;
	}
	return (i);
}


char	**ft_make_ourenvp(t_list **env)
{
	t_var	*var_tmp;
	t_list	*node_tmp;
	int		i;
	int		j;
	char	**our_envp;

	node_tmp = *env;
	i = ft_lst_onenv_size(env);
	our_envp = malloc(sizeof(char *) * (i + 1));
	if (our_envp == NULL)
		return (NULL);
	our_envp[i] = NULL;
	j = 0;
	while (node_tmp && j < i)
	{
		var_tmp = (t_var *)(node_tmp->content);
		if (var_tmp->on)
		{
			our_envp[j] = ft_fuse_var(var_tmp);
			if (our_envp[j] == NULL)
			{
				free_double_tab(our_envp);
				return (NULL);
			}
			j++;
		}
		node_tmp = node_tmp->next;
	}
	return (our_envp);
}




