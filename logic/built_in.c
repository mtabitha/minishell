#include "../minishell.h"

int    built_in_cmd(char **cmd, t_env *envi, char **path, char **env_mass)
{
    if (!ft_strncmp("echo", cmd[0], 4) && ft_strlen(cmd[0]) == 4)
        return (echo(cmd));
    else if (!ft_strncmp("export", cmd[0], 6) && ft_strlen(cmd[0]) == 6)
        return (export(envi, cmd));
    else if (!ft_strncmp("pwd", cmd[0], 3) && ft_strlen(cmd[0]) == 3)
        return (pwd(envi, cmd));
    else if (!ft_strncmp("unset", cmd[0], 5) && ft_strlen(cmd[0]) == 5)
        return (unset(envi, cmd));
    else if (!ft_strncmp("cd", cmd[0], 2) && ft_strlen(cmd[0]) == 2)
        return (cd(envi, cmd, path, env_mass));
    else if (!ft_strncmp("exit", cmd[0], 4) && ft_strlen(cmd[0]) == 4)
        return (exit_cmd(cmd));
    else if (!ft_strncmp("env", cmd[0], 3) && ft_strlen(cmd[0]) == 3)
        return (env(envi, cmd));
    return(1);
}