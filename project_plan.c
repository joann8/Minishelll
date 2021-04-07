
//Questions restante :
//	Comment fonctionne le stockage de l'historique de commande ?
//	Comment fonctionne les signaux ctrl + D / ctrl + C / ctrl + \?
//			ctrl + D  = EOF signal. No more input in stdin
//			ctrl + C  = Interrupt and return to upper process
//			ctrl +'\' = QUIT signal
//	Mesure le lvl de Shell (pour savoir quand exiter ?)





int		main(int argc, char **argv, char **envp)
{

	if (argc != 1 && ft_strcmp(argv[0], "./minishell"))
		return (1); // seulement minishell comme arg;
	
	int		quit_signal;
	char	*user_input;
	t_list	*env;

	// Grouper env + user_input + token_list dans une seule structure ?
	
	quit_signal = 0;
	env = ft_make_env_list(envp);
	while (get_next_line(0, &user_input) && quit_sig == 0)
	{
		printf(PROMPT);
		ft_store_user_input_in_history();//voir tgetent

		// Transforme le user_input en une seule grande liste token ( 0 word | 1 file_name | 2 pipe | 3 redir |  4 separator)
		// Chaque t_list token 
		// {
		//		void *data -> s_token;
		//		t_list *next_token;
		// }
		//
		//struct s_token
		//{
		//	enum type;
		//	char *str_val;
		//}
		t_list	*token_list = ft_get_token_list(user_input);

		// Compte les separators(';' ou '\n' ou '\0' dans GNL ?)
		int seq_nd = get_seq_number(token_list);
		
		// creer la table intermediaire de sequences, avec pour chaque sequence:
		//t_seq_lst
		//{
		//	t_list		*word; //regroupe tous les words
		//	t_list		*redir; //regroupe les differentes redirections
		//	int			pipe_total; //total de pipes dans la cmd (a | b | c ==> 2)   
		//	int			pipe_pos; // ou je me situe par rapport au pipe (0 (first), 1 ou 2 (last))
		//	t_seq_lst	*next_pipe;
		//}
		//
		//t_list *word
		//		void *data -> char *str word
		//		t_list *next
		//
		//t_list *redir, avec pour chaque noeud : enum > >> < + file_name associe
		//{
		//		void *data -> t_redir *redir;
		//		t_list *next;
		//}
		//		t_struct t_redir
		//			enum type
		//			char *file_name
		t_seq_lst tab_seq[seq_nb + 1];

		//Transmet les valeurs (word, redir etc..)des tokens aux sequences de commande;
		ft_assign_seq_tab(tab_seq, token_list);
		// Expansion des variables d'environnement
		ft_word_expansion(cmd_table, env);
		ft_delete_token_list(token_list);
		
		//t_list cmd_table
		//{
		//	void *data -> (t_simple_cmd )
		//	t_list *next;
		//}
		//
		//t_simple_cmd
		//{
		//	char	*job;
		//	char	**args;
		//	int		argc;
		//	int		fd_tab[2];
		//	int		fd_in;
		//	int		fd_out;
		//}
		
		t_list cmd_table[seq_nb + 1];
		// Assign :
		// 1->  Job & args
		// 2-> Opens the redirection & sets the accordings FD
		ft_assign_cmd_tale(tab_seq, cmd_table);
		
		// Execution ...;
		while (cmd_table[i])
		{
			t_list *tmp = cmd_table[i];
			while (tmp.data != NULL)
			{
				if (tmp.data->job == BUILTIN)
					ft_do_builtin(tmp.data);
				else
					ft_do_execve(tmp.data);
				tmp = tmp->next;
			}
			i++;
		}
	}
	return (0);
}









void		test()
{
	char *line;

	while(gnl(0, &line) && )
	{
