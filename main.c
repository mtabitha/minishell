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

void		close_fd(t_shell *shell)
{
	close(shell->fdin);
	close(shell->fdout);
	close(shell->pipein);
	close(shell->pipeout);
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
	if (unit->prev->type == APPEND)
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
		ft_putstr_fd("minishell: no such file or directory: ", 1);
		ft_putstr_fd(unit->str, 1);
		ft_putstr_fd("\n", 1);
	}
	dup2(shell->fdin, 0);
}

int		pipe_work(t_shell *shell, t_unit *unit)
{
	int			fd[2];

	pipe(fd);
	shell->ch_pid = fork();
	if (!shell->ch_pid)
	{
		close(fd[1]);
		shell->pipein = fd[0];
		dup2(fd[0], 0);
		return (0);
	}
	else
	{
		close(fd[0]);
		shell->pipein = fd[1];
		dup2(fd[1], 1);
		return (1);
	}
}

int			count_cmd(t_unit *unit)
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

char		**create_cmd(t_unit *unit)
{
	char 	**cmd;
	int		i;

	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (count_cmd(unit) + 1));
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

void		exec_cmd(t_shell *shell, t_unit *unit)
{
	char	**cmd;
	int		i;
	char 	*path;
	char	**env_mass;
	int		pid;
	int		ret;
	
	cmd = create_cmd(unit);
	env_mass = create_env_mass(shell->env);
	path = ft_strjoin("/bin/", *cmd);
	sig.pid = fork();
	if (!sig.pid)
	{

		ft_putstr_fd(path, 2);
		write(2, "\n", 1);
		execve(path, cmd, env_mass);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" - NOT FOUND COMMAND\n", 2);

		exit(127); // 127 command not found
	}
	else
		waitpid(sig.pid, &ret, 0);
	shell->ret = WEXITSTATUS(ret);
	shell->last_ret = shell->ret;
	if (sig.ch_flagint || sig.ch_flagquit)
	{
		shell->ret = sig.exit;
		shell->last_ret = sig.exit;
	}
	ft_putstr_fd(ft_itoa(shell->ret), 2);
	ft_putstr_fd(" - command return", 2);
	ft_putstr_fd(path, 2);
	write(2, "\n", 1);


	init_sig();
	ft_free(env_mass);
	ft_free(cmd);
	free(path);
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
	if (next && (next->type != END))
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
		if (shell->ch_pid != -1)
		{
			if (!shell->ch_pid)
			{
				ft_putstr_fd(ft_itoa(shell->ret), 2);
				ft_putstr_fd(" - child return\n", 2);
				exit(shell->ret);
			}
			else
			{
				waitpid(shell->ch_pid, &shell->ch_status, 0);
	    		shell->ch_ret = WEXITSTATUS(shell->ch_status);
				shell->last_ret = shell->ch_ret;
				shell->ret = shell->ch_ret;
				ft_putstr_fd(ft_itoa(shell->ch_ret), 2);
				ft_putstr_fd(" - pipe return\n", 2);
			}
		}
		shell->ch_pid = -1;
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
	shell.exit = 0;
	shell.ret = 0;
	shell.ch_pid = -1;
	shell.last_ret = 0;
	set_envs(&shell.env, env);
	set_shlvl(shell.env);
	init_termcap(&shell.tmp);
	init_fd(&shell);
	init_sig();
	while (shell.exit == 0)
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
