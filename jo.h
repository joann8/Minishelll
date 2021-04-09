//NOT USED FOR THE MOMENT

typedef struct	s_source
{
	char		*buffer;
	long		buffer_size;
	long		curpos;
}				t_source;

//tokenize_ft  NOT USED FOR THE MOMENT
char	next_char(t_source *src);
void	unget_char(t_source *src);
char	peek_char(t_source *src);
void	skip_whitespace(t_source *src);

//prompt
void	print_str(char *str);
int		print_error(int errno, char *error);

//print_help
void	print_list(t_list *list);
void	print_token(t_list *token);
void	print_seq(t_seq *tab_seq, int seq_nb);

//tokenize_utils
int		is_whitespace(char c);
int		comp(char c1, char c2);
void	escape_quote(char *str, int *pos);
int		look_second_quote(char c, char *str, int *pos);
//tokenize_assign
void	assign_type_1(t_list *token_list);
int		assign_type_2(t_list *head);
int 	assign_type_2_help(t_list **head, t_list **tmp, t_token *t2, t_token *t3);

//tokenize 
t_list	*ft_get_token_list(t_list *token_list, char *input);

// sequence utils
int		get_seq_number(t_list *token_list);
void	set_up_pipe_number(t_seq *tab_seq, int cmd_nb, int pipe_pos);
void	init_setup(t_seq *tab_seq, t_seq **tmp, int *pipe_pos, int cmd_nb);

//sequence
t_seq	*create_sequence(t_seq *tab_seq, t_list *token_list, int seq_nb);

//expansion utils
int		is_word(char *str);
int		is_var_name(char c);

//expansion length
void	manage_quotes(char c, int *i, int *j, int *quotes);
int		count_final_str(char *str, t_list *var, int quote);

//expansion str

char 	*assign_final_str(char *tmp, char *str, t_list *var, int quote);

//expansion
void escape_within_doubles(char *str, int *pos);
t_seq *make_expansion(t_seq *tab_seq, int seq_nb, t_list *var);
