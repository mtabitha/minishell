/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:48:38 by aahri             #+#    #+#             */
/*   Updated: 2021/05/26 18:57:42 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_str(char **cmd)
{
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(cmd[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	exit (255);
}

void	output_mistake_cd(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
}

int	info_mistake(char *cmd)
{
	ft_putstr_fd("minishell: export: `", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
	return (0);
}
