/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtabitha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:18:45 by mtabitha          #+#    #+#             */
/*   Updated: 2021/04/29 17:18:46 by mtabitha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			in_quote(char *str, int	pos)
{
	int		i;
	int		type;

	type = 0;
	i = -1;
	while (++i < pos && str[i])
	{
		if (i > 0 && str[i - 1] == '\\' && type != 1)
			;
		else if (!type && str[i] == '\'')
			type = 1;
		else if (!type && str[i] == '\"')
			type = 2;
		else if (type == 1 && str[i] == '\'')
			type = 0;
		else if (type == 2 && str[i] == '\"')
			type = 0;
	}
	return (type);
}

int		quote_err(char *line)
{
	if (in_quote(line, ft_strlen(line)))
	{
		ft_putstr_fd("minishell: Error: quote\n", 1);
		free(line);
		return (1);
	}
	return (0);
}


char *changing_tilda(void)
{
	char *home; 
	char *cwd;
	int len_home;
	int len_cwd;
	char *changed_path;
	int index;

	index = 0;
	changed_path = NULL;
	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(home, cwd, ft_strlen(home)))
	{
		len_home = ft_strlen(home);
		len_cwd = ft_strlen(cwd);
		changed_path = (char *)malloc(sizeof(char) * (len_cwd - len_home + 2));
		changed_path[len_cwd - len_home + 1] = 0;
		changed_path[0] = '~';
		while (cwd[len_home])
		{
			changed_path[index + 1] = cwd[len_home];
			len_home++;
			index++;
		}
	}
	else
		changed_path = getcwd(NULL, 0);
	free(cwd);
	return (changed_path);
}

t_unit		*parse(t_shell *shell)
{
	char 	*line;
	char *updated_path;
	line = NULL;

	updated_path = changing_tilda();
	ft_putstr_fd(updated_path, 2);
	ft_putstr_fd(" minishell > ", 1);
	set_flag(&shell->tmp, &shell->term);
	line = ft_strdup(termcap(&shell->tmp));
	reset_flag(&shell->term);
	if (sig.flagint)
		shell->last_ret = sig.exit;
	if (quote_err(line) || !line)
		return (NULL);
	line = space_line(line);
	shell->first = set_units(line);
	set_unit_type(shell->first);
	free(line);
	if (!check_valid(shell->first))
		shell->first = free_units(shell->first);
	return (shell->first);
}
