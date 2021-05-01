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

int			main(int argc, char *argv[], char **env)
{
    t_shell	shell;

	shell.exit = 0;
	ret_last_proc = 0;
	set_envs(&shell.env, env);
	set_shlvl(shell.env);
	while (shell.exit == 0)
	{
		parse(&shell);
			
	}
	return (0);
}
