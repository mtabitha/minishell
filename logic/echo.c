#include "../minishell.h"

int valid_flag_n(char *str)
{
    int i;

    i = 2;
    if (!ft_strncmp("-n", str, 2))
    {
        while (str[i] == 'n')
            i++;
    }
    if (str[i] == ' ' || !str[i])
        return (1);
    return (0);
}

int    check_n(char **str)
{
    if (str[0] && !ft_strncmp("-n", str[0], 2) && valid_flag_n(str[0]))
        return (1);
    return (0);
}

void    printf_echo(char **cmd)
{
    int ind;

    ind = 0;

    while (cmd[ind])
    {
        ft_putstr_fd(cmd[ind], 1);
        if (cmd[ind + 1])
            ft_putstr_fd(" ", 1);
        ind++;
    }
}

int     has_exclamation_sign(char **cmd)
{
    int ind;
    char *exc_sign;

    exc_sign = NULL;
    ind = 0;
    while (cmd[ind])
    {
        exc_sign = ft_strchr(cmd[ind], '!');
        if (exc_sign != NULL && exc_sign[0] == '!' && exc_sign[1])
        {
            ft_putstr_fd("bash: ", 1);
            ft_putstr_fd(exc_sign, 1);
            ft_putstr_fd(": event not found", 1);
            return (0);
        }
        ind++;
    }
    return (1);
}

int    echo(char **cmd)
{
    int i;

    i = 0;
    while (check_n(&cmd[i + 1]))
        i++;
    if (has_exclamation_sign(&cmd[i + 1]))
        printf_echo(&cmd[i + 1]);
    if (!i)
        ft_putstr_fd("\n", 1);
    return(0);
}