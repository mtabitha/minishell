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
	shell->fdin = -1;
	shell->fdout = -1;
}

void		close_fd(t_shell *shell)
{
	close(shell->fdin);
	close(shell->fdout);
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

void	redir(t_shell *shell, t_unit *unit)
{
	t_unit	*prev;
	t_unit	*next;

	prev = prev_type(unit);
	next = next_type(unit);
	if (prev)
	{
		if (prev->type == TRUNK)
			trunk_append(shell, unit);
		else if (prev->type == APPEND)
			trunk_append(shell, unit);
		else if (prev->type == IN)
			in(shell, unit);
	}
	if (next && (next->type != END))
		redir(shell, next->next);
}

int			count_cmd(t_unit *unit)
{
	int		i;

	i = 0;
	while (unit && unit->type != END)
	{
		if (unit->type < FILE)
			i++;
		unit = unit->next;
	}
	return (i);
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
	//int i = 0;
	//while(env_mass[i])
	//{
	//	printf("%s",env_mass[i++]);
	//	printf("\n");
	//}
	//printf("\n");
	return (env_mass);
}

void		exec_cmd(t_shell *shell, t_unit *unit)
{
	char	**cmd;
	int		i;
	char 	*path;
	char	**env_mass;
	int		fd[2];
	int		pid;
	
	pid = fork();
	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (count_cmd(unit) + 1));
	while (unit && unit->type != END)
	{
		if (unit->type < FILE)
			cmd[i++] = unit->str;
		unit = unit->next;
	}
	cmd[i] = NULL;
	i = 0;
	env_mass = create_env_mass(shell->env);
	path = ft_strjoin("/bin/", *cmd);
	if (!pid)
	{
		execve(path, cmd, env_mass);
	}
	else
		wait(&pid);
	ft_free(env_mass);
	ft_free(cmd);
	free(path);
}

void		run(t_shell *shell)
{
	t_unit	*unit;

	unit = shell->first;
	while (unit)
	{
		redir(shell, unit);
		exec_cmd(shell, unit);
		unit = null_or_end(unit);
		close_fd(shell);
		init_fd(shell);
		init_std(shell);
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
	set_envs(&shell.env, env);
	set_shlvl(shell.env);
	init_termcap(&shell.tmp);
	init_fd(&shell);
	while (shell.exit == 0)
	{
		init_sig();
		shell.first = parse(&shell);
		if (shell.first)
			run(&shell);
		//free_units(shell.first);	
	}
	//free_envs(shell.env);
	return (shell.ret);
}
