/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:06:51 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/17 13:06:52 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			count_argv(t_unit *unit)
{
	int		i;

	i = 0;
	while (unit && unit->type < PIPE)
	{
		if (unit->type < FILE)
			i++;
		unit = unit->next;
	}
	return (i);
}

char		**create_argv(t_unit *unit)
{
	char 	**cmd;
	int		i;

	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (count_argv(unit) + 1));
	while (unit && unit->type < PIPE)
	{
		if (unit->type < FILE)
			cmd[i++] = unit->str;
		unit = unit->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char		**create_env_mass(t_env *env)
{
	char	*env_arr;
	char	**env_mass;

	env_arr = ft_strdup(env->str);
	env_arr = ft_strjoin_for_gnl(env_arr, "\n");
	env = env->next;
	while(env)
	{
		env_arr = ft_strjoin_for_gnl(env_arr, env->str);
		env_arr = ft_strjoin_for_gnl(env_arr, "\n");
		env = env->next; 
	}
	env_mass = ft_split_str(env_arr, "\n");
	return (env_mass);
}

int		has_build_in(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
		return(1);
	else if (!ft_strncmp(cmd[0], "cd", 2) && ft_strlen(cmd[0]) == 2)
		return(1);
	else if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
		return(1);
	else if (!ft_strncmp(cmd[0], "export", 6) && ft_strlen(cmd[0]) == 6)
		return(1);
	else if (!ft_strncmp(cmd[0], "unset", 5) && ft_strlen(cmd[0]) == 5)
		return(1);
	else if (!ft_strncmp(cmd[0], "env", 3) && ft_strlen(cmd[0]) == 3)
		return(1);
	else if (!ft_strncmp(cmd[0], "exit", 4) && ft_strlen(cmd[0]) == 4)
		return(1);
	return (0);
}

void		exec_cmd(t_shell *shell, t_unit *unit)
{
	char	**argv;
	char 	**path;
	char	**envp;

	dollar(unit, shell);
	envp = create_env_mass(shell->env);
	argv = create_argv(unit);
	if (has_build_in(argv))
		shell->ret = built_in_cmd(argv, shell->env, path, envp);
	else
		shell->ret = exec_execve(shell->env, argv, envp);
	shell->last_ret = shell->ret;
	if (sig.ch_flagint || sig.ch_flagquit)
	{
		shell->ret = sig.exit;
		shell->last_ret = sig.exit;
	}
	init_sig();
	ft_free(argv);
	ft_free(envp);
	shell->recurs_exit = 1;
}