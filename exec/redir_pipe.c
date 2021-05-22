/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:00:51 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/17 13:00:53 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		pipe_work(t_shell *shell)
{
	int			fd[2];

	pipe(fd);
	shell->ch.pid = fork();
	if (!shell->ch.pid)
	{
		init_ch(&shell->ch);
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

void	redir_pipe(t_shell *shell, t_unit *unit)
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
			main_proc = pipe_work(shell);
	}
	if (next && (next->type != END) && !main_proc)
		redir_pipe(shell, next->next);
	if (!shell->recurs_exit && unit->type == CMD && !main_proc &&
			(!prev || prev->type >= PIPE))
		exec_cmd(shell, unit);
}