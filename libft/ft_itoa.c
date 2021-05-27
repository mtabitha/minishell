/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:35:11 by mtabitha          #+#    #+#             */
/*   Updated: 2020/10/31 15:37:23 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intcount(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	i;
	int		len;
	char	*ptr;

	i = n;
	len = ft_intcount(i);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len--] = '\0';
	if (!i)
		ptr[0] = '0';
	if (i < 0)
	{
		ptr[0] = '-';
		i *= -1;
	}
	while (i > 0)
	{
		ptr[len--] = '0' + (i % 10);
		i /= 10;
	}
	return (ptr);
}
