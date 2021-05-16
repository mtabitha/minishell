/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:19:47 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/24 09:19:49 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**take_path(t_env *envi)
{
	char **path;
	char *tmp;
	
	path = NULL;
	while (envi)
	{
		if (!ft_strncmp("PATH=", envi->str, 5))
		{
			path = ft_split_str(&envi->str[5], ":");
			int i = 0;
			while (path[i])
			{
				tmp = path[i];
				path[i] = ft_strjoin(path[i], "/");
				free(tmp);
				i++;
			}		
		}
		envi = envi->next;
	}
	return (path);
}

void		init_ch(t_child *ch)
{
	ch->pid = -1;
	ch->ret = 0;
	ch->status = 0;
}

void		init_pr(t_shell *shell)
{
	shell->ret = 0;
	shell->last_ret = 0;
	shell->main_proc = 1;
}

int			this_type(t_unit *unit, int type)
{
	if (unit->type == type)
		return (1);
	return (0);
}

int			this_types(char *tmp, t_unit *unit)
{
	if (ft_strchr(tmp, ' ') && this_type(unit, ETY))
		return (1);
	else if (ft_strchr(tmp, 'C') && this_type(unit, CMD))
		return (1);
	else if (ft_strchr(tmp, 'R') && this_type(unit, ARG))
		return (1);
	else if (ft_strchr(tmp, 'T') && this_type(unit, TRUNK))
		return (1);
	else if (ft_strchr(tmp, 'A') && this_type(unit, APPEND))
		return (1);
	else if (ft_strchr(tmp, 'I') && this_type(unit, IN))
		return (1);
	else if (ft_strchr(tmp, 'P') && this_type(unit, PIPE))
		return (1);
	else if (ft_strchr(tmp, 'E') && this_type(unit, END))
		return (1);
	return (0);
}

t_unit		*null_or_end(t_unit *unit)
{
	while (unit && unit->type < END)
		unit = unit->next;
	if (unit)
		return (unit->next);
	return (unit);
}

void		init_fd(t_shell *shell)
{
	shell->pipeout = -1;
	shell->pipein = -1;
	shell->fdin = -1;
	shell->fdout = -1;
}

void		fd_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void		close_fd(t_shell *shell)
{
	
	fd_close(shell->fdin);
	fd_close(shell->fdout);
	fd_close(shell->pipein);
	fd_close(shell->pipeout);
}

void		init_std(t_shell *shell)
{
	dup2(shell->in, 0);
	dup2(shell->out, 1);
}

t_unit		*prev_type(t_unit *unit)
{
	while (unit && unit->type < TRUNK)
		unit = unit->prev;
	return (unit);
}

t_unit		*next_type(t_unit *unit)
{
	while (unit && unit->type < TRUNK)
		unit = unit->next;
	return (unit);
}

void	trunk_append(t_shell *shell, t_unit *unit)
{
	if (shell->fdout > 0)
		close(shell->fdout);
	if (unit->prev->type == TRUNK)
		shell->fdout = open(unit->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		shell->fdout = open(unit->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	dup2(shell->fdout, 1);
}

void	in(t_shell *shell, t_unit *unit)
{
	if (shell->fdin > 0)
		close(shell->fdin);
	shell->fdin = open(unit->str, O_RDONLY | S_IRWXU);
	if (shell->fdin == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(unit->str, 1);
		ft_putstr_fd(": No such file or directory", 1);
		ft_putstr_fd("\n", 1);
		shell->last_ret = 1;
		shell->recurs_exit = 1;
		return ;
	}
	dup2(shell->fdin, 0);
}

int		pipe_work(t_shell *shell, t_unit *unit)
{
	int			fd[2];

	pipe(fd);
	shell->ch.pid = fork();
	if (!shell->ch.pid)
	{
		shell->main_proc = 0;
		sig.main_proc = 0;
		close(fd[1]);
		shell->pipein = fd[0];
		dup2(fd[0], 0);		
		return (0);
	}
	else
	{
		close(fd[0]);
		shell->pipeout = fd[1];
		dup2(fd[1], 1);
		return (1);
	}
}

int			count_argv(t_unit *unit)
{
	int		i;

	i = 0;
	while (unit && unit->type < PIPE)
	{
		if (unit->type < FILE)
			i++;
		unit = unit->next;
	}
	return (i);
}

char		**create_argv(t_unit *unit)
{
	char 	**cmd;
	int		i;

	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (count_argv(unit) + 1));
	while (unit && unit->type < PIPE)
	{
		if (unit->type < FILE)
			cmd[i++] = unit->str;
		unit = unit->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char		**create_env_mass(t_env *env)
{
	char	*env_arr;
	char	**env_mass;

	env_arr = ft_strdup(env->str);
	env_arr = ft_strjoin_for_gnl(env_arr, "\n");
	env = env->next;
	while(env)
	{
		env_arr = ft_strjoin_for_gnl(env_arr, env->str);
		env_arr = ft_strjoin_for_gnl(env_arr, "\n");
		env = env->next; 
	}
	env_mass = ft_split_str(env_arr, "\n");
	return (env_mass);
}

void			check_exist_file(char *filename, t_env *env, char **argv)
{
	char	**env_mass;
	char	**path;
	char	*cmd;
	int 	i;

	i = 0;
	env_mass = create_env_mass(env);
	path = take_path(env);
	while(path && path[i])
	{
		cmd = ft_strjoin_for_gnl(path[i++], filename);
		execve(cmd, argv, env_mass);
		free(cmd);
	}
	
}

int			exec_execve(t_env *env, char **argv, char **envp)
{
	int		ret;
	char	*filename;
	int		with_path;
	DIR		*dir;
	int		fd;
	
	with_path = 1;
	sig.pid = fork();
	if (!sig.pid)
	{
		filename = ft_strdup(*argv);
		if (!ft_strchr(filename, '/') && get_env("PATH=", env))
		{
			with_path = 0;
			check_exist_file(filename, env, argv);
		}
		execve(filename, argv, envp);
		fd = open(filename, O_RDWR);
		dir = opendir(filename);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		if (with_path == 0)
			ft_putstr_fd(": command not found\n", 2);
		else if (fd == -1 && dir != NULL)
			ft_putstr_fd(": is a directory\n", 2);
		else if (fd != -1 && dir == NULL)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
			
		closedir(dir);
		close(fd);
		exit(127);
	}	
	else
		waitpid(sig.pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

int		has_build_in(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
		return(1);
	else if (!ft_strncmp(cmd[0], "cd", 2) && ft_strlen(cmd[0]) == 2)
		return(1);
	else if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
		return(1);
	else if (!ft_strncmp(cmd[0], "export", 6) && ft_strlen(cmd[0]) == 6)
		return(1);
	else if (!ft_strncmp(cmd[0], "unset", 5) && ft_strlen(cmd[0]) == 5)
		return(1);
	else if (!ft_strncmp(cmd[0], "env", 3) && ft_strlen(cmd[0]) == 3)
		return(1);
	else if (!ft_strncmp(cmd[0], "exit", 4) && ft_strlen(cmd[0]) == 4)
		return(1);
	return (0);
}

void		exec_cmd(t_shell *shell, t_unit *unit)
{
	char	**argv;
	char 	**path;
	char	**envp;

	dollar(unit, shell);
	envp = create_env_mass(shell->env);
	argv = create_argv(unit);
	if (has_build_in(argv))
		shell->ret = built_in_cmd(argv, shell->env, path, envp);
	else
		shell->ret = exec_execve(shell->env, argv, envp);
	int		i = 0;
	//t_env *ptr = shell->env;
	//while (ptr)
	//{
	//	ft_putstr_fd(ptr->str, 1);
	//	ft_putstr_fd("\n", 1);
	//	ptr = ptr->next;
	//}

	shell->last_ret = shell->ret;
	if (sig.ch_flagint || sig.ch_flagquit)
	{
		shell->ret = sig.exit;
		shell->last_ret = sig.exit;
	}
	init_sig();
	ft_free(argv);
	ft_free(envp);
	shell->recurs_exit = 1;
}

void	redir(t_shell *shell, t_unit *unit)
{
	t_unit	*prev;
	t_unit	*next;
	int		main_proc;

	prev = prev_type(unit);
	next = next_type(unit);
	main_proc = 0;
	if (prev)
	{
		if (prev->type == TRUNK)
			trunk_append(shell, unit);
		else if (prev->type == APPEND)
			trunk_append(shell, unit);
		else if (prev->type == IN)
			in(shell, unit);
		else if (prev->type == PIPE)
			main_proc = pipe_work(shell, unit);
	}
	if (next && (next->type != END) && !main_proc)
		redir(shell, next->next);
	if (!shell->recurs_exit && unit->type == CMD && !main_proc &&
			(!prev || prev->type >= PIPE))
		exec_cmd(shell, unit);
}

void		run(t_shell *shell)
{
	t_unit	*unit;

	unit = shell->first;
	while (unit)
	{
		redir(shell, unit);
		unit = null_or_end(unit);
		close_fd(shell);
		init_fd(shell);
		init_std(shell);
		waitpid(-1, &shell->ch.status, 0);
		shell->ch.ret = WEXITSTATUS(shell->ch.status);
		if (shell->ch.ret)
		{
			shell->ret = shell->ch.ret;
			shell->last_ret = shell->ch.ret;
		}
		if (!shell->main_proc)
			exit(shell->ret);
		init_ch(&shell->ch);
		shell->recurs_exit = 0;
	}
}

int			main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
    t_shell	shell;
	shell.in = dup(0);
	shell.out = dup(1);

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	set_envs(&shell.env, env);
	set_shlvl(shell.env);
	init_pr(&shell);
	init_ch(&shell.ch);
	init_termcap(&shell.tmp);
	init_fd(&shell);
	init_sig();
	while (1)
	{
		shell.recurs_exit = 0;
		shell.first = parse(&shell);
		if (shell.first)
			run(&shell);
		//free_units(shell.first);	
	}
	//free_envs(shell.env);
	return (shell.ret);
}
