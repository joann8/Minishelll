#include "ft.h"

int		main(int argc, char **argv, char **envp)
{

	if (argc != 1 && ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
		return (1); // seulement minishell comme arg;
	
	int		quit_signal;
	char	*user_input;
	char	*line;
	char	*prompt;
	//t_list	*env;
	(void)envp;

	quit_signal = 0;
	//env = ft_make_env_list(envp);

	prompt = "minishell_says$";
	while (get_next_line(0, &line) && quit_signal == 0)
	{
		user_input = ft_strdup(line);
		printf("%s", prompt);
		printf("%s", user_input);
	}
	return (0);
}
