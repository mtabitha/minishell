/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:10:06 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/26 12:10:07 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**take_path(t_env *envi)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	while (envi)
	{
		if (!ft_strncmp("PATH=", envi->str, 5))
		{
			path = ft_split_str(&envi->str[5], ":");
			i = 0;
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

void	check_filename(char *filename, t_env *env, char **argv, char **envp)
{
	char	**path;
	char	*cmd;
	int		i;

	i = 0;
	path = take_path(env);
	while (path && path[i])
	{
		cmd = ft_strjoin_for_gnl(path[i++], filename);
		execve(cmd, argv, envp);
		free(cmd);
	}
}

int	count_argv(t_unit *unit)
{
	int	i;

	i = 0;
	while (unit && unit->type < PIPE)
	{
		if (unit->type < FILE)
			i++;
		unit = unit->next;
	}
	return (i);
}

char	**create_argv(t_unit *unit)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (count_argv(unit) + 1));
	if (!cmd)
		return (NULL);
	while (unit && unit->type < PIPE)
	{
		if (unit->type < FILE)
			cmd[i++] = ft_strdup(unit->str);
		unit = unit->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**create_env_mass(t_env *env)
{
	char	*env_arr;
	char	**env_mass;

	env_arr = ft_strdup(env->str);
	env_arr = ft_strjoin_for_gnl(env_arr, "\n");
	env = env->next;
	while (env)
	{
		env_arr = ft_strjoin_for_gnl(env_arr, env->str);
		env_arr = ft_strjoin_for_gnl(env_arr, "\n");
		env = env->next;
	}
	env_mass = ft_split_str(env_arr, "\n");
	free(env_arr);
	return (env_mass);
}
