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
	free(list->content);
	free(list);
}

int		empty_line(char *line)
{
	while (line && *line)
		if (*line != ' ' || *line != '\t')
			return (0);
		else
			line++;
	return (1);
}

char	*button_enter(t_termcap *tmp)
{
	write(1, "\n", 1);
	if (empty_line(tmp->new->content) && !tmp->in_hist )
	{
		free(tmp->new->content);
		return (NULL);
	}
	if (tmp->in_hist == 1)
	{
		tmp->in_hist = 0;
		free(tmp->new->content);
		tmp->new->content = ft_strdup(tmp->history->content);
	}
	tmp->new->next = tmp->first;
	if (tmp->first)
		tmp->first->prev = tmp->new;
	tmp->new->prev = NULL;
	tmp->first = tmp->new;
	tmp->history = tmp->first;
	tmp->count_hist++;
	delete_last_hist(tmp);
	return (tmp->first->content);
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
	clean_buf(tmp->buf);
	tmp->buf_len = read(0, tmp->buf, 100);
	if (sig.flag)
	{
		clean_buf(tmp->new->content);
		sig.flag = 0;
		tmp->pos = 0;
		tmp->history = NULL;
		tmp->in_hist = 0;
	}
}