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

t_unit	*prev_type(t_unit *unit)
{
	if (unit->type > FILE)
		return (NULL);
	while (unit && unit->type < TRUNK)
		unit = unit->prev;
	return (unit);
}

t_unit	*next_type(t_unit *unit)
{
	while (unit && unit->type < TRUNK)
		unit = unit->next;
	return (unit);
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
	if (!shell->recurs_exit && unit->type == CMD && !main_proc
		&& (!prev || prev->type >= PIPE))
		exec_cmd(shell, unit);
}
