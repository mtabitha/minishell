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
	while (shell.exit == 0)
	{
		init_sig();
		parse(&shell);
		//if (shell.first != NULL && valid_units(&shell))
		//	;
		//free_units(shell.first);	
	}
	//free_envs(shell.env);
	return (shell.ret);
}
