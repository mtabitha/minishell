/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:19:54 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/24 09:19:56 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"
# include <termios.h>
# include <term.h>

# define ETY  0
# define CMD  1
# define ARG  2
# define TRUNK 3
# define APPEND 4
# define IN   5
# define PIPE 6
# define END  7

# define UP 	"\x1b[A"
# define DOWN 	"\x1b[B"
# define LEFT 	"\x1b[D"
# define RIGHT 	"\x1b[C"
# define BACK 	"\x7f"
# define ENTER	"\n"

typedef struct		s_env
{
	struct s_env	*next;
	char			*str;	
}					t_env;					

typedef struct		s_unit
{
	struct s_unit	*next;
	struct s_unit	*prev;
	int				type;
	char			*str;
}					t_unit;

typedef struct	s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	char			*content;
}				t_list;

typedef struct 	s_termcap
{
	int			pos;
	int			max;
	char 		buf[100];
	int			buf_len;
	int			in_hist;
	int			count_hist;
	t_list		*new;
	t_list		*first;
	t_list		*history;
}				t_termcap;

typedef struct		s_shell
{
	int				ret;
	int				in;
	int				out;
	t_env			*env;
	t_unit			*first;
	int				exit;
	t_termcap 		tmp;
	struct termios 	term;
}					t_shell;

char		*get_env_val(t_env *env);
t_env		*get_env(char *type, t_env *env);
void		set_envs(t_env **mini_env, char **bash_env);
void		set_shlvl(t_env *env);

void		parse(t_shell *shell);

char		*space_line(char *line);
void		set_unit_type(t_unit *unit);
t_unit		*set_units(char *line, t_env *env);
void		dollar(t_unit *unit, t_shell *shell);
int			in_quote(char *str, int	pos);
int			check_valid(t_unit *first);
t_unit		*free_units(t_unit *unit);

int			change_quote(char ch, char *quote);
void		space_skip(char *line, int *i);
void		free_null(char **ptr);
void		ft_free(char **ptr);
int			count_el(char **ptr);

char	*termcap(t_termcap *tmp);
void	set_flag(t_termcap *tmp, struct termios *term);
void	reset_flag(struct termios *term);
void	init_termcap(t_termcap *tmp);

void	button_up(t_termcap *tmp);
void	button_down(t_termcap *tmp);
void	button_right(t_termcap *tmp);
void	button_left(t_termcap *tmp);
void	button_enter(t_termcap *tmp);
void	button_back(t_termcap *tmp);
void	button_insert(t_termcap *tmp);
void	button_read(t_termcap *tmp);
void	delete_ch(char **buf, int pos);
void	add_ch(char **buf, int pos, char *str);

#endif
