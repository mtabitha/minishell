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