/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:29:02 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:29:03 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			add_space(char *line, int i)
{
	if ((!i || (i && line[i - 1] != '\\' )) && !in_quote(line, i)
			&& ft_strchr("<>;|", line[i]))
		return (1);
	return (0);
}

int			count_ch(char *line)
{
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (line[++i])
		if (add_space(line, i) == 1)
			count++;
	return (i + 2 * count);
}

char		*space_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(new_line = (char *)malloc((count_ch(line) + 1) * sizeof(char))))
		return (NULL);
	while (line[i])
		if (add_space(line, i))
		{
			new_line[j++] = ' ';
			new_line[j++] = line[i++];
			if (line[i] == '>')
				new_line[j++] = line[i++];
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i++];
	new_line[j] = 0;
	free(line);
	return (new_line);
}
