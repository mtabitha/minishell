/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:58:21 by aahri             #+#    #+#             */
/*   Updated: 2021/05/26 20:22:29 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int	has_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void	free_double_mass(char **split_path)
{
	int	ind;

	if (split_path)
	{
		ind = 0;
		while (split_path[ind])
		{
			free(split_path[ind]);
			ind++;
		}
		free(split_path);
	}
}

int	got_file_from_home(t_env *envi, int ind, int nbr, char *joined_path)
{
	struct stat		buf;
	char			**split_path;

	split_path = NULL;
	while (envi)
	{
		if (!ft_strncmp(envi->str, "PATH=", 5))
		{
			split_path = ft_split_str(&envi->str[5], ":");
			while (nbr == -1 && split_path[ind])
			{
				joined_path = ft_strjoin(split_path[ind], "/env");
				nbr = stat(joined_path, &buf);
				free(joined_path);
				ind++;
			}
		}
		envi = envi->next;
	}
	free_double_mass(split_path);
	if (!nbr)
		return (1);
	return (0);
}

int	env(t_env *envi, char **unit)
{
	int	ret;

	ret = 0;
	if (unit[1] || !got_file_from_home(envi, 0, -1, NULL))
	{
		ft_putstr_fd("minishell: env: ", 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (127);
	}
	while (envi)
	{
		if (has_equal(envi->str))
		{
			ft_putstr_fd(envi->str, 1);
			ft_putstr_fd("\n", 1);
		}
		envi = envi->next;
	}
	return (0);
}
