#include "../minishell.h"

int	valid_arg(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] != '_' && !ft_isalpha (cmd[i]))
		return (info_mistake(cmd));
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] != '_' && !ft_isalpha(cmd[i])
			&& !ft_isdigit(cmd[i]) && cmd[i] != '=')
			return (info_mistake(cmd));
		i++;
	}
	return (1);
}

char	*left_part(char *arr)
{
	char	*str;
	int		len;

	len = 0;
	while (arr[len] && arr[len] != '=')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	len--;
	while (len >= 0)
	{
		str[len] = arr[len];
		len--;
	}
	return (str);
}

int	cmp_unit_env(char **cmd, t_env *envi, char *left_cmd, int ind)
{
	char	*left_envi;
	char	*tmp;
	t_env	*time;

	time = envi;
	while (envi)
	{
		left_envi = left_part(envi->str);
		if (!ft_strncmp(left_cmd, left_envi, ft_strlen(left_cmd))
			&& ft_strlen(left_cmd) == ft_strlen(left_envi))
		{
			if (has_equal(cmd[ind]))
			{
				tmp = envi->str;
				envi->str = ft_strdup(cmd[ind]);
				free(tmp);
			}
			free(left_envi);
			return (0);
		}
		free(left_envi);
		envi = envi->next;
	}
	return (1);
}

int	check_valid_export(char **cmd, t_env *envi)
{
	char	*left_cmd;
	int		ind;
	int		ret;

	ret = 0;
	ind = 0;
	while (cmd[ind])
	{
		if (valid_arg(cmd[ind]))
		{
			left_cmd = left_part(cmd[ind]);
			if (cmp_unit_env(&cmd[ind], envi, left_cmd, 0))
				ft_lstadd_back(&envi, ft_lstnew(cmd[ind]));
			free(left_cmd);
		}
		else
			ret = 1;
		ind++;
	}
	return (ret);
}

int	export(t_env *envi, char **cmd)
{
	char	**split_strs;
	int		ret;
	t_env	*envi_dup;
	int		exc_sign;

	split_strs = NULL;
	ret = 0;
	exc_sign = 1;
	envi_dup = NULL;
	if (cmd && cmd[1])
		exc_sign = has_exclamation_sign(&cmd[1]);
	if (cmd && cmd[1] == NULL)
	{
		lstdup(&envi_dup, envi);
		sorting_env(envi_dup);
		output_sorted_env(envi_dup, split_strs);
		delete_lst(envi_dup);
	}
	else if (cmd && cmd[1] && exc_sign)
		return (check_valid_export(&cmd[1], envi));
	if (!exc_sign)
		ft_putstr_fd("\n", 1);
	return (0);
}
