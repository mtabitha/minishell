#include "../minishell.h"

int     has_equal(char *str)
{
    while (*str)
    {
        if (*str == '=')
            return (1);
        str++;
    }
    return (0);
}

int    env(t_env *envi, char **unit)
{
    int ret;

    ret = 0;
    if (unit[1])
    {
        ft_putstr_fd("env: ‘", 1);
        ft_putstr_fd(unit[1], 1);
        ft_putstr_fd("’: No such file or directory\n", 1);
        return (127);
    }
    while (envi)
    {
        if (has_equal(envi->str))
        {
            ft_putstr_fd(envi->str, 1);
            ft_putstr_fd("\n", 1);
        }
        envi = envi->next;
    }
    return (0);
}