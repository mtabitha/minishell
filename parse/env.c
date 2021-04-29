/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:10:08 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:10:10 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		set_envs(t_env **mini_env, char **bash_env)
{
	t_env	*env;
	t_env	*next;
	int		i;

	i = 0;
	next = NULL;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return ;
	env->next = NULL;
	env->str = ft_strdup(bash_env[i]);
	*mini_env = env;
	while (bash_env && bash_env[++i])
	{
		if (!(next = (t_env *)malloc(sizeof(t_env))))
			return ;
		next->str = ft_strdup(bash_env[i]);
		next->next = NULL;
		env->next = next;
		env = env->next;
	}
}

t_env		*get_env(char *type, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(type, env->str, ft_strlen(type)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char		*get_env_val(t_env *env)
{
	int		i;

	i = -1;
	while (env && env->str[++i])
		if (env->str[i] == '=')
			return (&env->str[i + 1]);
	return (NULL);
}
