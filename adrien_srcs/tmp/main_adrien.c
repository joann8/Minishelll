#include "../ft.h"


int		main(int argc, char **argv, char **envp)
{

	if (argc != 1 && ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
		return (1); // seulement minishell comme arg;
	
	t_list	*env_list;
	char	*line;

	while (get_next_line(0, &line) == 1)
	{
		printf("[adconsta:minishell_says$] ");
		printf("%s\n", line);
		free(line);
	}
	free(line);
	//Contenu de chaque noeud POINTE sur une ligne du tableau, (n'en contient pas une copie !);
	env_list = ft_doubletab_to_list(envp); 
	ft_print_str_list(env_list);
	ft_free_lst(env_list);
	return (0);
}
