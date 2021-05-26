/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:08:46 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:08:47 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_null(char **ptr)
{
	if (ptr && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free(char **ptr)
{
	int		i;

	i = 0;
	if (!*ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	count_el(char **ptr)
{
	int	n;

	n = 0;
	if (!ptr)
		return (n);
	while (ptr[n])
		n++;
	return (n);
}

void	space_skip(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	change_quote(char ch, char *quote)
{
	if (*quote == ' ')
	{
		*quote = ch;
		return (1);
	}
	else if (*quote == ch)
	{
		*quote = ' ';
		return (1);
	}
	return (0);
}
