/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_arrow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:36:22 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/08 14:36:23 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_history(t_termcap *tmp, char *line)
{
	tmp->max = ft_strlen(line);
	tmp->pos = tmp->max;
    write(1, line, tmp->max);
}

void	button_up(t_termcap *tmp)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs("\x1b[J", 1, ft_putchar);
	if (tmp->first == NULL)
		write_history(tmp, tmp->new->content);
	else
	{
		if (!tmp->in_hist)
		{
			tmp->in_hist = 1;
			tmp->history = tmp->first;
		}
		else if (tmp->history && tmp->history->next)
			tmp->history = tmp->history->next;
		write_history(tmp, tmp->history->content);
	}
}

void	button_down(t_termcap *tmp)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs("\x1b[J", 1, ft_putchar);
	if (tmp->history == NULL || tmp->history->prev == NULL)
	{
		tmp->in_hist = 0;
		write_history(tmp, tmp->new->content);
	}
	else
	{
		if (tmp->history->prev)
			tmp->history = tmp->history->prev;
		write_history(tmp, tmp->history->content);
	}
}

void	button_right(t_termcap *tmp)
{
	if (tmp->pos == tmp->max)
		return ;
	tmp->pos++;
	tputs(cursor_right, 1, ft_putchar);
}

void	button_left(t_termcap *tmp)
{
	if (!tmp->pos)
		return ;
	tmp->pos--;
	tputs(cursor_left, 1, ft_putchar);
}
