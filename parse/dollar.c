/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:14:21 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:14:22 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			count_dollar(char *str, int i, int type)
{
	int		count;

	count = 0;
	while (!type && str[i] && str[i] != -36)
	{
		count++;
		i++;
	}
	while (type && str[i] && str[i] != -36 && str[i] != ' ')
	{
		count++;
		i++;
	}
	return (count);
}

void		set_str_dollar(char *str, int *i, char *line, int type)
{
	int		j;

	j = 0;
	while (!type && str[*i] && str[*i] != -36)
		line[j++] = str[(*i)++];
	while (type && str[*i] && str[*i] != -36 && str[*i] != ' ')
		line[j++] = str[(*i)++];
	line[j] = 0;
}

char		*parse_dollar(char *str, t_env *env)
{
	char	*new_str;
	char 	*line;
	char	*type;
	int		i;

	i = 0;
	new_str = NULL;
	line = NULL;
	type = NULL;
	while (str[i])
	{
		if (str[i] == -36)
			if (str[i + 1] == '?' && (i += 2))
				line = ft_itoa(ret_last_proc);
			else 
			{
				type = (char *)malloc(sizeof(char) * (count_dollar(str, ++i, 1) + 1));
				set_str_dollar(str, &i, type, 1);
				line = ft_strdup(get_env_val(get_env(type, env)));
			}
		else
		{
			line = (char *)malloc(sizeof(char) * (count_dollar(str, i, 0) + 1));
			set_str_dollar(str, &i, line, 0);
		}
		new_str = ft_strjoin_for_gnl(new_str, line);
		free_null(&line);
		free_null(&type);
	}
	free(str);
	return (new_str);
}
