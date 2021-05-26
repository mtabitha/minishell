/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:00:18 by aahri             #+#    #+#             */
/*   Updated: 2021/05/25 21:05:12 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_digits(char *str)
{
	int	index;

	index = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (str[index])
		index++;
	return (index);
}

int	is_our_diapason(char *str)
{
	int	sign;
	int	index;
	int	delta;

	index = 0;
	sign = 1;
	delta = 1;
	if (*str == '-' || sign == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (count_digits(str) == 19 && sign == 1)
		delta = ft_strncmp("9223372036854775807", str, 19);
	else if (count_digits(str) == 19 && sign == -1)
		delta = ft_strncmp("9223372036854775808", str, 19);
	if (delta >= 0)
		return (1);
	return (0);
}

int	is_nbr(char *str)
{
	int		nbr;
	int		index;

	index = 0;
	nbr = 1;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			nbr = 0;
		index++;
	}
	if (nbr && count_digits(str) <= 19 && is_our_diapason(str))
		return (1);
	return (0);
}

unsigned char	get_value(char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (sign == 1)
		return ((unsigned char)num);
	return (256 - (unsigned char)num);
}

int	exit_cmd(char **cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (cmd && cmd[1])
	{
		if (!is_nbr(cmd[1]))
			arg_str(cmd);
		else
		{
			if (cmd[2])
			{
				ft_putstr_fd("bash: exit: too many arguments\n", 2);
				return (1);
			}
			exit(get_value(cmd[1]));
		}
	}
	exit (0);
}
