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
	if (sig.pid != -1)
	{
		sig.ch_flagquit = 1;
		if (!sig.main_proc)
			return ;
		ft_putstr_fd("Quit: 3\n", 2);
		sig.exit = 131;
	}
}

void	handle_sigint(int ret)
{
	(void)ret;
	if (sig.pid != -1)
	{
		sig.ch_flagint = 1;
		write(2, "\n", 1);
		sig.exit = 130;
	}
	else
	{
		sig.flagint = 1;
		sig.exit = 1;
		write(2, "\n", 2);
		print_minishell();
	}
}

void	init_sig(void)
{
	sig.exit = 0;
	sig.pid = -1;
	sig.flagint = 0;
	sig.flag = 0;
	sig.ch_flagquit = 0;
	sig.ch_flagint = 0;
	sig.main_proc = 1;
}
