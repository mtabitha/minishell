/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:09:15 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/17 13:09:17 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**take_path(t_env *envi)
{
	char **path;
	char *tmp;
	
	path = NULL;
	while (envi)
	{
		if (!ft_strncmp("PATH=", envi->str, 5))
		{
			path = ft_split_str(&envi->str[5], ":");
			int i = 0;
			while (path[i])
			{
				tmp = path[i];
				path[i] = ft_strjoin(path[i], "/");
				free(tmp);
				i++;
			}		
		}
		envi = envi->next;
	}
	return (path);
}

void			check_exist_file(char *filename, t_env *env, char **argv)
{
	char	**env_mass;
	char	**path;
	char	*cmd;
	int 	i;

	i = 0;
	env_mass = create_env_mass(env);
	path = take_path(env);
	while(path && path[i])
	{
		cmd = ft_strjoin_for_gnl(path[i++], filename);
		execve(cmd, argv, env_mass);
		free(cmd);
	}
}

int		print_error(char *filename, t_env *env)
{
	int		ret;
	DIR		*dir;
	int		fd;

	ret = 127;
	fd = open(filename, O_RDWR);
	dir = opendir(filename);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	if (!ft_strchr(filename, '/') && get_env("PATH=", env))
		ft_putstr_fd(": command not found\n", 2);
	else if (fd == -1 && dir != NULL  && (ret = 126))
		ft_putstr_fd(": is a directory\n", 2);
	else if (fd != -1 && dir == NULL && (ret = 126))
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	if (dir)
		closedir(dir);
	close(fd);
	return (ret);
}

int			exec_execve(t_env *env, char **argv, char **envp)
{
	int		ret;
	char	*filename;

	sig.pid = fork();
	if (!sig.pid)
	{
		filename = ft_strdup(*argv);
		if (!ft_strchr(filename, '/') && get_env("PATH=", env))
			check_exist_file(filename, env, argv);
		execve(filename, argv, envp);
		ret = print_error(filename, env);
		exit(ret);
	}	
	else
		waitpid(sig.pid, &ret, 0);
	return (WEXITSTATUS(ret));
}