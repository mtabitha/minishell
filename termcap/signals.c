/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:51 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/11 15:31:52 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		handle_sigquit(int ret)
{
	char	*str;

	str = ft_itoa(ret);
	if (sig.pid != -1)
	{
		sig.ch_flagquit = 1;
		if (!sig.main_proc)
			return ;
		ft_putstr_fd("Quit: ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
		sig.exit = 131;
	}
	free(str);
}

void		handle_sigint(int ret)
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
		ft_putstr_fd(getcwd(NULL, 0), 2);
		ft_putstr_fd(" minishell > ", 2);//?
	}
}

void		init_sig(void)
{
	sig.exit = 0;
	sig.pid = -1;
	sig.flagint = 0;
	sig.flag = 0;
	sig.ch_flagquit = 0;
	sig.ch_flagint = 0;
	sig.main_proc = 1;
}