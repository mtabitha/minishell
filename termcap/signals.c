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
	if (sig.pid)
	{
		sig.flag = 1;
		write(1, "\n", 1);
		ft_putstr_fd("^\\Quit: ", 2);
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
		sig.exit = 131;
	}
	free(str);
}

void		handle_sigint(int ret)
{
	sig.flag = 1;
	if (sig.pid)
	{
		write(1, "\n", 1);
		ft_putstr_fd("^C", 1);
		sig.exit = 130;
	}
	else
		sig.exit = 1;
	write(1, "\n", 1);
	ft_putstr_fd("minishell > ", 2);
	tputs(delete_character, 1, ft_putchar);
}

void		init_sig(void)
{
	sig.exit = 0;
	sig.pid = 0;
	sig.flag = 0;
}