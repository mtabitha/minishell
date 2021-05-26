/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:08:16 by aahri             #+#    #+#             */
/*   Updated: 2021/05/26 16:16:13 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_lst(t_env *envi_dup)
{
	t_env	*tmp;

	while (envi_dup)
	{
		tmp = envi_dup;
		envi_dup = envi_dup->next;
		free(tmp->str);
		free(tmp);
	}
}
