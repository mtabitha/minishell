/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:11:34 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:11:36 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	shlvl_valid(char *nbr)
{
	int		count;
	int		i;
	char	**ptr;

	i = 0;
	count = 0;
	ptr = ft_split_str(nbr, " \t\n\r\v\f");
	count = count_el(ptr);
	while (ptr[0][i])
	{
		if (ptr[0][i] == '+' || ptr[0][i] == '-')
			i++;
		if (!ft_isdigit(ptr[0][i]) || count != 1)
		{
			ft_free(ptr);
			return (0);
		}
		i++;
	}
	ft_free(ptr);
	return (1);
}

void	set_shlvl(t_env *env)
{
	int		nbr;
	char	*arr_nbr;

	env = get_env("SHLVL", env);
	arr_nbr = ft_strdup(get_env_val(env));
	if (!shlvl_valid(arr_nbr))
		nbr = 1;
	else if (ft_atoi(arr_nbr) < 0)
		nbr = 0;
	else
		nbr = ft_atoi(arr_nbr) + 1;
	free(arr_nbr);
	free(env->str);
	arr_nbr = ft_itoa(nbr);
	env->str = ft_strjoin("SHLVL=", arr_nbr);
	free(arr_nbr);
}
