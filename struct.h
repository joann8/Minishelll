/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:25:25 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 18:45:02 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

typedef	struct	s_gnl
{
	//int		index; 
//	pid_t		pid[2];
	int			shell_level;
	int			exit_status;
}				t_gnl;

typedef	enum	e_type
{
	WORD,
	FILENAME,
	SEPARATOR,
	PIPE,
	IN,
	OUT,
	APPEND
}				t_e_type;

typedef struct	s_token
{
	t_e_type	e_type;
	char		*tok_str;
}				t_token;

typedef struct		s_seq
{
	t_list		 	*word;
	t_list			*redir;
	int				pipe_total;
	int				pipe_pos;
	struct s_seq	*next_pipe;
}					t_seq;

typedef struct		s_redir
{
	t_e_type		e_type;
	char			*file_name;
}					t_redir;

typedef struct		s_simple_cmd
{
	char			*job;
	char			**av;
	int				ac;
	int				fd_in;
	int				fd_out;
	int				pipe_mod; //0 N // 1 Y
	int				pipe_pos; // -1 first 0middle 1 last 
	int				retour;
}					t_simple_cmd;

typedef struct		s_var
{
	char			*name;
	char			*value;
}					t_var;

typedef	struct	s_term
{

	int		col;
	int		line;
	char	*name; // trouve le nom du terminal
	char	*AF; //definie la couleur du texte
	char	*AB; //definie la couleur du background
	char	*cl; // delete text
	char	*cm; // bouge curseur
	char	*md; // texte gras
	char	*mb; //texte clignotant
	char	*us; //txt souligne
	char	*me; //reset les params
	char	*cb; //clear du curseur -> begining of line
	char	*ch; //replace le curseur a la position P
	char	*ce; // clear to EOL
	char	*rc;
	char	*sc;
	char	*cd;
}				t_term;


typedef	struct s_input
{
	unsigned int	i;
	unsigned int	log_size;
	char			buf[5];
	char			*screen;
	char			*input;
}		t_input;
	
typedef struct	s_expansion
{
	char		*str;
	char		*var_str;
	char 		*tmp;
	int			i;
	int			j;
	int 		quote;
	int			mod;
}				t_expansion;

typedef struct	s_pipe
{
	int			fd_tab[2];
	int			fd_in_to_use;
	int			fd_out_to_use;
	int			fd_in_next;
}				t_pipe;
#endif
