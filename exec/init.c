/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:56:42 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/17 12:56:44 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void		init_std(t_shell *shell)
{
	dup2(shell->in, 0);
	dup2(shell->out, 1);
}

void		init_fd(t_shell *shell)
{
	shell->pipeout = -1;
	shell->pipein = -1;
	shell->fdin = -1;
	shell->fdout = -1;
}
