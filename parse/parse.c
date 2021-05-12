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

t_unit		*parse(t_shell *shell)
{
	char 	*line;

	line = NULL;
	ft_putstr_fd("minishell > ", 1);
	set_flag(&shell->tmp, &shell->term);
	line = ft_strdup(termcap(&shell->tmp));
	reset_flag(&shell->term);
	if (quote_err(line) || !line)
		return (NULL);
	line = space_line(line);
	shell->first = set_units(line, shell->env);
	dollar(shell->first, shell);
	free(line);
	if (!check_valid(shell->first))
		shell->first = free_units(shell->first);
	t_unit *start;
	start = shell->first;
	//if (start)
	//{
	//while (start)
	//{
	//	ft_putstr_fd(start->str, 1);
	//	ft_putstr_fd(" ", 1);
	//	ft_putstr_fd(ft_itoa(start->type), 1);
	//	start = start->next;
	//	ft_putstr_fd(" ", 1);
	//}
	//}
	//write(1, "\n", 1);

	return (shell->first);



}
