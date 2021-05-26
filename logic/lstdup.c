/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:07:41 by aahri             #+#    #+#             */
/*   Updated: 2021/05/25 21:46:23 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lstdup(t_env **envi_dup, t_env *envi)
{
	t_env	*lst;

	while (envi)
	{
		lst = ft_lstnew (envi->str);
		ft_lstadd_back (envi_dup, lst);
		envi = envi->next;
	}
}
