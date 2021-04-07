typedef struct	s_source
{
	char		*buffer;
	long		buffer_size;
	long		curpos;
}				t_source;

//prompt
void	print_str(char *str);

//tokenize_utils
int		is_whitespace(char c);
int		is_word(char *str);
int		is_specific(char c1, char c2);
int		look_second_quote(char c, char *str, int *pos);

//tokenize_ft
char	next_char(t_source *src);
void	unget_char(t_source *src);
char	peek_char(t_source *src);
void	skip_whitespace(t_source *src);



