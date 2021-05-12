/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 11:32:16 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/04 11:32:18 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		type_error(t_unit *unit)
{
	char 	*str;

	str = "newline";
	if (unit)
		str = unit->str;
	ft_putstr_fd("\n",1);	
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\"", 1);
	return (1);
}

int			no_valid_unit(t_unit *unit)
{
	if (unit->next == NULL || (unit->next && unit->next->type != FILE))
	{
		if (unit->type == TRUNK)
			return (type_error(unit->next));
		else if (unit->type == APPEND)
			return (type_error(unit->next));
		else if (unit->type == IN)
			return (type_error(unit->next));
	}
	if (unit->prev == NULL || (unit->prev && unit->prev->type > FILE))
	{
		if (unit->type == PIPE)
			return (type_error(unit));
		else if (unit->type == END)
			return (type_error(unit));
	}
	return (0);
}

t_unit		*free_units(t_unit *unit)
{
	t_unit	*ptr;

	while (unit)
	{
		ptr = unit->next;
		free(unit->str);
		free(unit);
		unit = ptr;
	}
	return (NULL);
}

int		check_valid(t_unit *first)
{
	t_unit 	*unit;
	int		flag;

	flag = 0;
	unit = first;
	while (unit)
	{
		if (no_valid_unit(unit))
			return (0);
		unit = unit->next;
	}
	return (1);
}
