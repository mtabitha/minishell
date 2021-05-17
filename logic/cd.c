#include "../minishell.h"

int    cd(t_env *envi, char **cmd)
{
    int     answer;
    char    **split_home;
    char    *cmd_exp[3];
    char    *tmp_getcwd;
    t_env   *ptr;
    int     ret;

    ret = 0;
    ptr = envi;
    answer = 0;
    cmd_exp[0] = "export";
    cmd_exp[2] = NULL;
    if (!ft_strncmp("cd", cmd[0], 2) && ft_strlen(cmd[0]) == 2)
    {
        if (!cmd[1] || (cmd[1] && (!ft_strncmp("~", cmd[1], 1) && ft_strlen(cmd[1]) == 1)))
        {
            while (envi && ft_strncmp("HOME=", envi->str, 5))
                envi = envi->next;
            if (envi)
            {
                split_home = ft_split_str(envi->str, "=");
                answer = chdir(split_home[1]);
                free(split_home[0]);
                free(split_home[1]);
                free(split_home);
            }
        }
        else if (cmd[1])
            answer = chdir(cmd[1]);
        if (answer)
        {
            ft_putstr_fd("bash: cd: ", 1);
            ft_putstr_fd(cmd[1], 1);
            ft_putstr_fd(": No such file or directory\n", 1);
            ret = 1;
        }
        tmp_getcwd = getcwd(NULL, 0);
        cmd_exp[1] = ft_strjoin("PWD=", tmp_getcwd);
        export(ptr, cmd_exp);
        free(tmp_getcwd);
    }
    return(ret);
}