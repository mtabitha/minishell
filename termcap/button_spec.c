/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:37:26 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/08 14:37:28 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_last_hist(t_termcap *tmp)
{
	t_list	*ptr;
	t_list	*list;

	if (tmp->count_hist < 15)
		return ;
	list = tmp->first;
	while(list && list->next)
		list = list->next;
	if (list->prev)
	{
		ptr = list->prev;
		ptr->next = NULL;
	}
	free(list);
}

char	*button_enter(t_termcap *tmp)
{
	if (ft_strcmp(tmp->new->content, "") || tmp->in_hist == 1)
	{
		if (tmp->in_hist == 1)
		{
			free(tmp->new->content);
			tmp->new->content = ft_strdup(tmp->history->content);
		}
		tmp->new->next = tmp->first;
		if (tmp->first)
			tmp->first->prev = tmp->new;
		tmp->new->prev = NULL;
		tmp->first = tmp->new;
		tmp->history = tmp->first;
		tmp->new = (t_list *)malloc(sizeof(t_list));
		tmp->new->content = ft_strdup("");
		tmp->count_hist++;
		delete_last_hist(tmp);
		return (tmp->first->content);
	}
	return (tmp->new->content);
	write(1, ENTER, 1);
}

void	button_back(t_termcap *tmp)
{
	if (tmp->in_hist == 1)
	{
		tmp->in_hist = 0;
		free(tmp->new->content);
		tmp->new->content = ft_strdup(tmp->history->content);
	}
	if (tmp->pos)
	{
		tmp->pos--;
		delete_ch((char **)&(tmp->new->content), tmp->pos);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	tmp->max = ft_strlen(tmp->new->content);
}

void	button_insert(t_termcap *tmp)
{
	if (tmp->in_hist == 1)
	{
		tmp->in_hist = 0;
		free(tmp->new->content);
		tmp->new->content = ft_strdup(tmp->history->content);
	}
	tputs(enter_insert_mode, 1, ft_putchar);
	add_ch((char **)&(tmp->new->content), tmp->pos, tmp->buf);
	write(1, tmp->buf, tmp->buf_len);
	tputs(exit_insert_mode, 1, ft_putchar);
	tmp->pos += tmp->buf_len;
	tmp->max = ft_strlen(tmp->new->content);
}

void	button_read(t_termcap *tmp)
{
	int	i;

	i = 0;
	while (i < 4)
		tmp->buf[i++] = 0;
	tmp->buf_len = read(0, tmp->buf, 100);
}