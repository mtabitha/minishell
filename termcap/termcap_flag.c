/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:29:01 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/08 14:30:05 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_flag(t_termcap *tmp, struct termios *term)
{
	char	*term_name;

	term_name = getenv("TERM");
	if (tcgetattr(0, term) < 0)
		return (1);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, term) < 0)
		return (1);
	tgetent(0, term_name);
	tmp->pos = 0;
	tmp->max = 0;
	tmp->new = (t_list *)malloc(sizeof(t_list));
	if (!tmp->new)
		return (1);
	tmp->new->content = ft_strdup("");
	return (0);
}

void	reset_flag(struct termios *term)
{
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, term);
}

void	init_termcap(t_termcap *tmp)
{
	tmp->count_hist = 0;
	tmp->in_hist = 0;
	tmp->pos = 0;
	tmp->first = NULL;
	tmp->history = NULL;
}
