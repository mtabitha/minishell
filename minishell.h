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

# define ETY  0
# define CMD  1
# define ARG  2
# define TRUNK 3
# define APPEND 4
# define IN   5
# define PIPE 6
# define END  7

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


typedef struct		s_shell
{
	int				ret;
	int				in;
	int				out;
	t_env			*env;
	t_unit			*first;
	int				exit;
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

#endif
