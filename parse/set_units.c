/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_units.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:17:07 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:17:10 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			count_new_unit_str(char *line, int i)
{
	int		count;
	char	quote;

	count = 0;
	quote = ' ';
	while (line[i] && (line[i] != ' ' || quote != ' '))
	{
		if (line[i] == '\\' && (quote == ' ' || (quote == '\"'
				&& ft_strchr("$\\\"", line[i + 1]))))
			i++;
		else if ((quote == ' ' || quote == '\"') &&
					line[i] == '$' && !ft_strchr("$ ", line[i + 1]))
			line[i] = -line[i];
		else if (line[i] == '\"' || line[i] == '\'')
			count -= change_quote(line[i], &quote);
		count++;
		i++;
	}
	return (count);
}

void 		parse_new_unit_str(char *line, char *new_str, int *i)
{
	char	quote;
	int		j;

	j = 0;
	quote = ' ';
	while (line[*i] && (line[*i] != ' ' || quote != ' '))
		if (line[*i] == '\\' && (quote == ' ' || (quote == '\"'
				&& ft_strchr("$\\\"", line[*i + 1]))))
		{
			new_str[j++] = line[++(*i)];
			(*i)++;
		}
		else if (line[*i] == '\"' || line[*i] == '\'')
			change_quote(line[(*i)++], &quote);
		else
			new_str[j++] = line[(*i)++];
	new_str[j] = 0;
}

t_unit		*new_unit_str(char *line, int *i, t_env *env)
{
	t_unit	*new;
	char	*new_str;
	char	*ptr;

	if (!(new = (t_unit *)malloc(sizeof(t_unit))) ||
			!(new_str = (char *)malloc(sizeof(char) *
				(count_new_unit_str(line, *i) + 1))))
		return (NULL);
	parse_new_unit_str(line, new_str, i);
	if (ft_strchr(new_str, (char)(-36)))
		new_str = parse_dollar(new_str, env);
	new->str = ft_strdup(new_str);
	free(new_str);
	return (new);
}

void		set_unit_type(t_unit *unit)
{
	if (!ft_strncmp("", unit->str, 1))
		unit->type = ETY;
	else if (!ft_strncmp(">", unit->str, 1))
		unit->type = RED1;
	else if (!ft_strncmp(">>", unit->str, 2))
		unit->type = RED2;
	else if (!ft_strncmp("<", unit->str, 1))
		unit->type = IN;
	else if (!ft_strncmp("|", unit->str, 1))
		unit->type = PYPE;
	else if (!ft_strncmp(";", unit->str, 1))
		unit->type = END;
	else if (unit->prev == NULL || unit->prev->type >= PYPE)
		unit->type = CMD;
	else
		unit->type = ARG;	
}

t_unit		*set_units(char *line, t_env *env)
{
	t_unit	*unit;
	t_unit	*next;
	int		i;

	i = 0;
	unit = NULL;
	next = NULL;
	space_skip(line, &i);
	while (line[i])
	{
		next = new_unit_str(line, &i, env);
		next->prev = unit;
		next->next = NULL;
		if (unit)
			unit->next = next;
		unit = next;
		set_unit_type(unit);
		space_skip(line, &i);
	}
	while (next && next->prev)
		next = next->prev;
	return (next);
}
