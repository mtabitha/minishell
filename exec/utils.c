/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahri <aahri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:05:36 by mtabitha          #+#    #+#             */
/*   Updated: 2021/05/26 21:19:34 by aahri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	off_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	on_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

char	*get_changed_path(char *home, char *cwd)
{
	int		len_home;
	int		len_cwd;
	int		index;
	char	*changed_path;

	index = 0;
	len_home = ft_strlen(home);
	len_cwd = ft_strlen(cwd);
	changed_path = (char *)malloc(sizeof(char) * (len_cwd - len_home + 2));
	memory_allocated(changed_path);
	changed_path[len_cwd - len_home + 1] = 0;
	changed_path[0] = '~';
	while (cwd[len_home])
	{
		changed_path[index + 1] = cwd[len_home];
		len_home++;
		index++;
	}
	return (changed_path);
}

char	*changing_tilda(void)
{
	char	*home;
	char	*cwd;
	char	*changed_path;
	int		index;

	index = 0;
	changed_path = NULL;
	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(home, cwd, ft_strlen(home)))
		changed_path = get_changed_path(home, cwd);
	else
		changed_path = getcwd(NULL, 0);
	free(cwd);
	return (changed_path);
}

int	empty_line(char *line)
{
	while (line && *line)
	{
		if (*line != ' ' || *line != '\t')
			return (0);
		else
			line++;
	}
	return (1);
}
