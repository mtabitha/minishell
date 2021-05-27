/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:04:05 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/24 15:04:06 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_for_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s || s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_for_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = ft_strlen_for_gnl(s1);
	j = ft_strlen_for_gnl(s2);
	ptr = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	if (s1)
		free(s1);
	ptr[i] = '\0';
	return (ptr);
}

int	get_next_line(int fd, char **line)
{
	int		flag;
	int		i;
	char	buf[10000];

	i = 0;
	flag = 1;
	while (flag)
	{
		flag = read(fd, &buf[i], 1);
		if (!flag || buf[i] == '\n')
		{
			buf[i] = 0;
			*line = ft_strdup(buf);
			if (flag)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (flag);
}
