/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:25:59 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/08 14:26:01 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_buf(char *buf)
{
	while (buf && *buf)
		*buf++ = 0;
}

void	delete_ch(char **buf, int pos)
{
	int	len;

	len = ft_strlen(*buf);
	(*buf)[pos] = 0;
	if (len == pos)
		return ;
	*buf = ft_strjoin_for_gnl(*buf, &(buf[0][pos + 1]));
}

void	add_ch(char **buf, int pos, char *str)
{
	int		len;
	char	*ptr;

	len = ft_strlen(*buf);
	if (len == pos)
	{
		*buf = ft_strjoin_for_gnl(*buf, str);
		return ;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 2));
	ft_strlcpy(ptr, *buf, pos + 1);
	ptr[pos] = str[0];
	ft_strlcpy(&ptr[pos + 1], &(buf[0][pos]), len - pos + 1);
	free(*buf);
	*buf = ptr;
}

void	button_eof(t_termcap *tmp)
{
	if (*(tmp->new->content) == 0 && !tmp->in_hist)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else
		write(1, "\a", 1);
}

char	*termcap(t_termcap *tmp)
{
	while (1)
	{
		button_read(tmp);
		if (!ft_strcmp(tmp->buf, ENTER))
			return (button_enter(tmp));
		else if (!ft_strcmp(tmp->buf, UP))
			button_up(tmp);
		else if (!ft_strcmp(tmp->buf, DOWN))
			button_down(tmp);
		else if (!ft_strcmp(tmp->buf, RIGHT))
			button_right(tmp);
		else if (!ft_strcmp(tmp->buf, LEFT))
			button_left(tmp);
		else if (!ft_strcmp(tmp->buf, BACK))
			button_back(tmp);
		else if (!ft_strcmp(tmp->buf, END_L))
			button_eof(tmp);
		else
			button_insert(tmp);
	}
	return (tmp->first->content);
}
