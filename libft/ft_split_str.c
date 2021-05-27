/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:05:01 by mtabitha          #+#    #+#             */
/*   Updated: 2021/03/08 12:07:32 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	i_d(char c, const char *del)
{
	while (*del)
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}

static int	ft_c(char *s, const char *del)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && i_d(*s, del))
			s++;
		if (*s)
		{
			i++;
			while (*s && !i_d(*s, del))
				s++;
		}
	}
	return (i);
}

static char	*ft_stralloc(char *s, const char *del)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !i_d(s[i], del))
		i++;
	word = (char *)malloc(i + 1);
	i = 0;
	if (word)
	{
		while (s[i] && !i_d(s[i], del))
		{
			word[i] = s[i];
			i++;
		}
		word[i] = '\0';
	}
	return (word);
}

char	**ft_split_str(char const *s, const char *del)
{
	int		i;
	char	**mass;

	i = 0;
	mass = (char **)malloc((ft_c((char *)s, del) + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	if (mass)
	{
		while (*s)
		{
			while (*s && i_d(*s, del))
				s++;
			if (*s && !i_d(*s, del))
			{
				mass[i++] = ft_stralloc((char *)s, del);
				if (!mass[i - 1])
					return (NULL);
				while (*s && !i_d(*s, del))
					s++;
			}
		}
		mass[i] = NULL;
	}
	return (mass);
}
