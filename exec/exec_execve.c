/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:09:15 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/26 17:24:12 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ret_error(int *ret, int fd, DIR *dir)
{
	if (fd == -1 && dir != NULL)
	{
		*ret = 126;
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (fd != -1 && dir == NULL)
	{
		*ret = 126;
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

int	print_error(char *filename, t_env *env)
{
	int	ret;
	DIR	*dir;
	int	fd;

	ret = 127;
	fd = open(filename, O_RDWR);
	dir = opendir(filename);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	if (!ft_strchr(filename, '/') && get_env("PATH", env))
		ft_putstr_fd(": command not found\n", 2);
	else
		ret_error(&ret, fd, dir);
	if (dir)
		closedir(dir);
	close(fd);
	return (ret);
}

int	its_minishell(char *filename)
{
	char	*ptr;

	ptr = ft_strchr(filename, '/');
	if (!ptr)
		return (0);
	ptr++;
	while (ptr)
	{
		if (!ft_strchr(ptr, '/'))
		{
			if (!(ft_strcmp("minishell", ptr)))
				return (1);
			else
				return (0);
		}
		ptr = ft_strchr(ptr, '/') + 1;
	}
	return (0);
}

int	exec_execve(t_shell *shell, char **argv, char **envp)
{
	int		ret;
	char	*filename;

	ret = 0;
	filename = ft_strdup(*argv);
	if (its_minishell(filename))
		off_signal();
	sig.pid = fork();
	if (!sig.pid)
	{
		if (!ft_strchr(filename, '/') && get_env("PATH", shell->env))
			check_filename(filename, shell->env, argv, envp);
		else
			execve(filename, argv, envp);
		ret = print_error(filename, shell->env);
		exit(ret);
	}	
	else
		waitpid(sig.pid, &ret, 0);
	on_signal();
	free(filename);
	return (WEXITSTATUS(ret));
}
