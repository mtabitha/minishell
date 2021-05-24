/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:05:36 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/17 13:05:40 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_unit		*prev_type(t_unit *unit)
{
	if (unit->type > FILE)
		return (NULL);
	while (unit && unit->type < TRUNK)
		unit = unit->prev;
	return (unit);
}

t_unit		*next_type(t_unit *unit)
{
	while (unit && unit->type < TRUNK)
		unit = unit->next;
	return (unit);
}

char *changing_tilda(void)
{
	char *home; 
	char *cwd;
	int len_home;
	int len_cwd;
	char *changed_path;
	int index;

	index = 0;
	changed_path = NULL;
	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(home, cwd, ft_strlen(home)))
	{
		len_home = ft_strlen(home);
		len_cwd = ft_strlen(cwd);
		changed_path = (char *)malloc(sizeof(char) * (len_cwd - len_home + 2));
		changed_path[len_cwd - len_home + 1] = 0;
		changed_path[0] = '~';
		while (cwd[len_home])
		{
			changed_path[index + 1] = cwd[len_home];
			len_home++;
			index++;
		}
	}
	else
		changed_path = getcwd(NULL, 0);
	free(cwd);
	return (changed_path);
}

int	empty_line(char *line)
{
	while (line && *line)
	{
		if (*line != ' ' || *line != '\t')
			return (0);
		else
			line++;
	}
	return (1);
}