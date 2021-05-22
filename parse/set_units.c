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
			line[i] = DOLLAR;
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
		{
			if (!change_quote(line[(*i)], &quote))
				new_str[j++] = line[(*i)];
			(*i)++;
		}
		else
			new_str[j++] = line[(*i)++];
	new_str[j] = 0;
}

t_unit		*new_unit_str(char *line, int *i)
{
	t_unit	*new;
	char	*new_str;

	if (!(new = (t_unit *)malloc(sizeof(t_unit))) ||
			!(new_str = (char *)malloc(sizeof(char) *
				(count_new_unit_str(line, *i) + 1))))
		return (NULL);
	if (line[*i] == '\'' || line[*i] == '\"')
		new->in_quote = 1;
	else
		new->in_quote = 0;
	parse_new_unit_str(line, new_str, i);
	new->str = new_str;
	return (new);
}

void		set_unit_type(t_unit *unit)
{
	while (unit)
	{
		if (!ft_strncmp("", unit->str, 1) && !unit->in_quote)
			unit->type = ETY;
		else if (!ft_strncmp(">", unit->str, 2) && !unit->in_quote)
			unit->type = TRUNK;
		else if (!ft_strncmp(">>", unit->str, 3) && !unit->in_quote)
			unit->type = APPEND;
		else if (!ft_strncmp("<", unit->str, 2) && !unit->in_quote)
			unit->type = IN;
		else if (!ft_strncmp("|", unit->str, 2) && !unit->in_quote)
			unit->type = PIPE;
		else if (!ft_strncmp(";", unit->str, 2) && !unit->in_quote)
			unit->type = END;
		else if (unit->prev == NULL || unit->prev->type >= PIPE)
			unit->type = CMD;
		else if (unit->prev->type >= TRUNK && unit->prev->type <= IN)
			unit->type = FILE;
		else
			unit->type = ARG;
		unit = unit->next;
	}	
}

t_unit		*set_units(char *line)
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
		next = new_unit_str(line, &i);
		next->prev = unit;
		next->next = NULL;
		if (unit)
			unit->next = next;
		unit = next;
		space_skip(line, &i);
	}
	while (next && next->prev)
		next = next->prev;
	return (next);
}
