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
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>

# define ETY  0
# define CMD  1
# define ARG  2
# define FILE 3
# define TRUNK 4
# define APPEND 5
# define IN   6
# define PIPE 7
# define END  8

# define UP 	"\x1b[A"
# define DOWN 	"\x1b[B"
# define LEFT 	"\x1b[D"
# define RIGHT 	"\x1b[C"
# define BACK 	"\x7f"
# define ENTER	"\n"
# define END_L	"\x04"

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

typedef struct		s_child
{
	pid_t			pid;
	int				ret;
	int				status;
}					t_child;


typedef struct		s_shell
{
	int				recurs_exit;
	int				pipein;
	int				pipeout;
	int				fdout;
	int				fdin;
	int				main_proc;
	int				ret;
	int				last_ret;
	int				status;
	int				in;
	int				out;
	t_child			ch;
	t_env			*env;
	t_unit			*first;
	t_termcap 		tmp;
	struct termios 	term;
}					t_shell;

typedef struct		s_sig
{
	pid_t			pid;
	int				flag;
	int				flagint;
	int				exit;
	int				ch_flagint;
	int				ch_flagquit;
	int				main_proc;
}					t_sig;

t_sig		sig;

char		*get_env_val(t_env *env);
t_env		*get_env(char *type, t_env *env);
void		set_envs(t_env **mini_env, char **bash_env);
void		set_shlvl(t_env *env);

t_unit		*parse(t_shell *shell);

char		*space_line(char *line);
void		set_unit_type(t_unit *unit);
t_unit		*set_units(char *line);
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
char	*button_enter(t_termcap *tmp);
void	button_back(t_termcap *tmp);
void	button_insert(t_termcap *tmp);
void	button_read(t_termcap *tmp);
void	delete_ch(char **buf, int pos);
void	add_ch(char **buf, int pos, char *str);

void		handle_sigquit(int ret);
void		handle_sigint(int ret);
void		init_sig(void);
void	clean_buf(char *buf);

char		**create_env_mass(t_env *env);
void	redir_pipe(t_shell *shell, t_unit *unit);
void		exec_cmd(t_shell *shell, t_unit *unit);
int			exec_execve(t_env *env, char **argv, char **envp);
t_unit		*next_type(t_unit *unit);
t_unit		*prev_type(t_unit *unit);
void		init_ch(t_child *ch);
void		init_pr(t_shell *shell);
void		init_std(t_shell *shell);
void		init_fd(t_shell *shell);

int         built_in_cmd(char **cmd, t_env *envi);
void        ft_lstadd_back(t_env **lst, t_env *new);
int         echo(char **cmd);
int         exit_cmd(char **cmd);
int         env(t_env *envi, char **unit);
int         pwd(char **cmd);//показать Чингизу
t_env       *ft_lstnew(void *content);
int         export(t_env *envi, char **cmd);
void        copy_back(t_env *dst, t_env *src, int len_args_unit);
int         has_equal(char *str);
void        sorting_env(t_env *envi);
void        output_sorted_env(t_env *envi, char **split_strs);
int         unset(t_env *envi, char **cmd);
char        *left_part(char *arr);
int         cd(t_env *envi, char **cmd);
int         valid_arg(char *cmd);
int         has_exclamation_sign(char **cmd);
#endif
