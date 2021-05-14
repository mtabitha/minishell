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
		ft_putstr_fd("Quit: ", 1);
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
		sig.exit = 131;
	}
	free(str);
}

void		handle_sigint(int ret)
{
	if (sig.pid != -1)
	{
		sig.ch_flagint = 1;
		write(1, "\n", 1);
		sig.exit = 130;
	}
	else
	{
		sig.flagint = 1;
		sig.exit = 1;
		write(1, "\n", 1);
		ft_putstr_fd("minishell > ", 2);
		tputs(delete_character, 1, ft_putchar);
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
}