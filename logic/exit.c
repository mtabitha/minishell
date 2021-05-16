#include "../minishell.h"

int    exit_cmd(char **cmd)
{
    ft_putstr_fd("exit\n", 1);
    if (cmd[1])
    {
        ft_putstr_fd("minishell: exit: ", 1);
        ft_putstr_fd(cmd[1], 1);
        ft_putstr_fd(": numeric argument required\n", 1);
        exit (255);
    }
    exit (0);
}