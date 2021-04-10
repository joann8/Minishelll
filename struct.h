/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:25:25 by jacher            #+#    #+#             */
/*   Updated: 2021/04/10 10:33:10 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

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
	int		e_type;
	char	*tok_str;
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
	int				e_type;
	char			*file_name;
}					t_redir;

typedef struct		s_simple_cmd
{
	char			*job;
	char			**av;
	int				ac;
	int				fd_tab[2];
	int				fd_in;
	int				fd_out;
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
}				t_term;

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

#endif
