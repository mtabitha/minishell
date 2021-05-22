#include "../minishell.h"

void    replace_str(t_env *envi, t_env *start_envi, char *left_envi)
{
    size_t len_envi;
    char    *left_going;
    char *left_start_envi;

    len_envi = ft_strlen(left_envi);
    while (start_envi)
    {    
        if (start_envi->next)
            left_going = left_part(start_envi->next->str);
        left_start_envi = left_part(start_envi->next->str);
        if (!ft_strncmp(left_going, left_envi, len_envi) && len_envi == ft_strlen(left_start_envi))
        {
            start_envi->next = envi->next;
            free(envi->str);
            envi->next = NULL;
            free(envi);
            free(left_going);
            free(left_start_envi);
            break;
        }
        else
        {
            start_envi = start_envi->next;
            free(left_going);
            free(left_start_envi);
        }
    }
}

int    valid_arg_without_output(char *cmd)
{
    int i;

    i = 0;
    if (cmd[i] != '_' && !ft_isalpha(cmd[i]))
        return (0);
    while (cmd[i] && cmd[i] != '=')
    {
        if (cmd[i] != '_' && !ft_isalpha(cmd[i]) && !ft_isdigit(cmd[i]) && cmd[i] != '=')
            return (0);
        i++;
    }
    return (1);
}

int     unset(t_env *envi, char **cmd)
{
    char *left_cmd;
    char *left_envi;
    t_env *start_envi;
    int ind;
    int ret;

    ind = 1;
    ret = 0;
    start_envi = envi;
    while (cmd && cmd[ind])
    {
        left_cmd = left_part(cmd[ind]);
        while (valid_arg(cmd[ind]) && envi)
        {
            left_envi = left_part(envi->str);
            if (!ft_strncmp(left_cmd, left_envi, ft_strlen(left_cmd)) && ft_strlen(left_cmd) == ft_strlen(left_envi))
            {
                replace_str(envi, start_envi, left_envi);
                envi = start_envi;
                free(left_envi);
                break ;
            }
            free(left_envi);
            envi = envi->next;
        }
        free(left_cmd);
        if (!valid_arg_without_output(cmd[ind]))
            ret = 1;
        ind++;
    }
    return (ret);
}