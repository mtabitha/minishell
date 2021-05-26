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

#include "../minishell.h"

t_unit	*null_or_end(t_unit *unit)
{
	while (unit && unit->type < END)
		unit = unit->next;
	if (unit)
		return (unit->next);
	return (unit);
}

void	fd_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	close_fd(t_shell *shell)
{
	fd_close(shell->fdin);
	fd_close(shell->fdout);
	fd_close(shell->pipein);
	fd_close(shell->pipeout);
}

void	run(t_shell *shell)
{
	t_unit	*unit;

	unit = shell->first;
	while (unit)
	{
		redir_pipe(shell, unit);
		unit = null_or_end(unit);
		close_fd(shell);
		init_fd(shell);
		init_std(shell);
		wait(&shell->ch.status);
		shell->ch.ret = WEXITSTATUS(shell->ch.status);
		if (shell->ch.pid != -1)
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

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	on_signal();
	set_envs(&shell.env, env);
	set_shlvl(shell.env);
	init_pr(&shell);
	while (1)
	{
		shell.recurs_exit = 0;
		shell.first = parse(&shell);
		if (shell.first)
			run(&shell);
		free_units(shell.first);
	}
	return (shell.ret);
}
