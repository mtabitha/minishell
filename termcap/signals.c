/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:51 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/17 19:13:51 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigquit(int ret)
{
	(void)ret;
	if (g_sig.pid != -1)
	{
		g_sig.ch_flagquit = 1;
		if (!g_sig.main_proc)
			return ;
		ft_putstr_fd("Quit: 3\n", 2);
		g_sig.exit = 131;
	}
}

void	handle_sigint(int ret)
{
	(void)ret;
	if (g_sig.pid != -1)
	{
		g_sig.ch_flagint = 1;
		write(2, "\n", 1);
		g_sig.exit = 130;
	}
	else
	{
		g_sig.flag = 1;
		g_sig.flagint = 1;
		g_sig.exit = 1;
		write(2, "\n", 2);
		print_minishell();
		tputs(save_cursor, 1, ft_putchar);
	}
}

void	init_sig(void)
{
	g_sig.exit = 0;
	g_sig.pid = -1;
	g_sig.flagint = 0;
	g_sig.flag = 0;
	g_sig.ch_flagquit = 0;
	g_sig.ch_flagint = 0;
	g_sig.main_proc = 1;
}
