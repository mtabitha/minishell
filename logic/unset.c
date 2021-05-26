#include "../minishell.h"

void	free__mass(char *mass1, char *mass2, t_env *envi)
{
	free(mass1);
	free(mass2);
	if (envi)
		free(envi);
}

void	replace_str(t_env *envi, t_env *start_envi, char *left_envi)
{
	size_t	len_envi;
	char	*left_going;
	char	*left_start_envi;

	len_envi = ft_strlen (left_envi);
	while (start_envi)
	{
		if (start_envi->next)
			left_going = left_part(start_envi->next->str);
		left_start_envi = left_part(start_envi->next->str);
		if (!ft_strncmp(left_going, left_envi, len_envi)
			&& len_envi == ft_strlen(left_start_envi))
		{
			start_envi->next = envi->next;
			free(envi->str);
			envi->next = NULL;
			free__mass(left_going, left_start_envi, envi);
			break ;
		}
		else
		{
			start_envi = start_envi->next;
			free__mass(left_going, left_start_envi, NULL);
		}
	}
}

int	valid_arg_without_output(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] != '_' && !ft_isalpha(cmd[i]))
		return (0);
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] != '_' && !ft_isalpha(cmd[i])
			&& !ft_isdigit(cmd[i]) && cmd[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	cmp_left_side(char *left_envi,
	char *left_cmd, t_env *start_envi, t_env *envi)
{
	left_envi = left_part(envi->str);
	if (!ft_strncmp (left_cmd, left_envi, ft_strlen(left_cmd))
		&& ft_strlen (left_cmd) == ft_strlen (left_envi))
	{
		replace_str (envi, start_envi, left_envi);
		free (left_envi);
		return (1);
	}
	free(left_envi);
	return (0);
}

int	unset(t_env *envi, char **cmd, int ind)
{
	char	*left_cmd;
	char	*left_envi;
	t_env	*start_envi;
	int		ret;

	left_envi = NULL;
	ret = 0;
	start_envi = envi;
	while (cmd && cmd[ind])
	{
		left_cmd = left_part(cmd[ind]);
		while (valid_arg(cmd[ind]) && envi)
		{
			if (cmp_left_side(left_envi, left_cmd, start_envi, envi))
				break ;
			envi = envi->next;
		}
		envi = start_envi;
		free(left_cmd);
		if (!valid_arg_without_output(cmd[ind]))
			ret = 1;
		ind++;
	}
	return (ret);
}
