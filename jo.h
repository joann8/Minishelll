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

//tokenize_utils
int		is_whitespace(char c);
int		is_word(char *str);
int		is_spec(char c1, char c2);
int		look_second_quote(char c, char *str, int *pos);

//tokenize 
t_list	*ft_get_token_list(t_list *token_list, char *input);
void	assign_type_1(t_list *token_list);
int		assign_type_2(t_list *token_list);

//sequence
int create_sequence(t_seq *tab_seq, t_list *token_list);
