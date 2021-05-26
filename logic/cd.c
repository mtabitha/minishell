/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:56:10 by aahri             #+#    #+#             */
/*   Updated: 2021/05/25 20:52:34 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>
#include <string.h>

int	close_fd_dir(int fd, DIR *dir)
{
	close(fd);
	if (dir)
		closedir(dir);
	return (1);
}

int	dir_or_file_or_not(char **cmd)
{
	DIR		*dir;
	int		fd;

	if (cmd[1] && cmd[1][0] != '\0' &&
			!(!ft_strncmp(cmd[1], "~", 1) && ft_strlen(cmd[1]) == 1))
	{
		fd = open(cmd[1], O_RDONLY);
		dir = opendir(cmd[1]);
		if (fd != -1 && !dir)
		{
			output_mistake_cd("minishell: cd: ", cmd[1], ": Not a directory\n");
			return (close_fd_dir(fd, dir));
		}
		else if (fd == -1 && !dir)
		{
			output_mistake_cd("minishell: cd: ",
				cmd[1], ": No such file or directory\n");
			return (close_fd_dir(fd, dir));
		}
		else if (dir)
			chdir(cmd[1]);
		close_fd_dir(fd, dir);
	}
	return (0);
}

int	has_tilda(char **cmd, int ret, t_env *envi)
{
	char	*home;

	if (cmd[1] && !ft_strncmp(cmd[1], "~", 1)
		&& ft_strlen(cmd[1]) == 1)
	{
		while (envi && (ft_strncmp("HOME=", envi->str, 5)))
			envi = envi->next;
		home = getenv("HOME");
		if (!envi || (!ft_strncmp(home, &envi->str[5], ft_strlen(home))
				&& ft_strlen(home) == ft_strlen(&envi->str[5])))
		{
			chdir(getenv("HOME"));
			return (0);
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	return (ret);
}

int	non_arg(char **cmd, int ret, t_env *envi)
{
	char	*mass[3];

	mass[0] = "cd";
	mass[2] = NULL;
	if (!cmd[1])
	{
		while (envi && ft_strncmp(envi->str, "HOME=", 5))
			envi = envi->next;
		if (envi)
		{
			mass[1] = &envi->str[5];
			return (dir_or_file_or_not(mass));
		}
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	return (ret);
}

int	cd(t_env *envi, char **cmd)
{
	int		ret;
	char	*cmd_exp[3];
	char	*tmp_getcwd;
	t_env	*ptr;

	ptr = envi;
	cmd_exp[0] = "export";
	cmd_exp[2] = NULL;
	ret = 0;
	ret = dir_or_file_or_not(cmd);
	ret = has_tilda(cmd, ret, envi);
	ret = non_arg(cmd, ret, envi);
	tmp_getcwd = getcwd(NULL, 0);
	cmd_exp[1] = ft_strjoin("PWD=", tmp_getcwd);
	export(ptr, cmd_exp);
	free(tmp_getcwd);
	free(cmd_exp[1]);
	return (ret);
}
