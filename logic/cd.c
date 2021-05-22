#include "../minishell.h"

int     count_smbls(char *adr)
{
    int len;
    int counter;

    counter = 0;
    len = 0;
    while (adr[len] && counter < 3)
    {
        if (adr[len] == '/')
            counter++;
        len++;
    }
    if (adr[len - 1] == '/')
        len--;
    return (len);
}

void    making_tilda(char **tilda_adr, char *adr, int len)
{
    *tilda_adr = (char *)malloc(sizeof(char) * (len + 1));
    (*tilda_adr)[len] = '\0';
    while (len--)
        (*tilda_adr)[len] = adr[len];
}

char    *get_tilda()
{
    char *adr;
    char *tilda_adr;
    int len;

    adr = getcwd(NULL, 0);
    len = count_smbls(adr);
    making_tilda(&tilda_adr, adr, len);
    free(adr);
    return (tilda_adr);
}

int    cd(t_env *envi, char **cmd)
{
    int     answer;
    char    *cmd_exp[3];
    char    *tmp_getcwd;
    t_env   *ptr;
    int     ret;
    char *adr;

    ret = 0;
    ptr = envi;
    answer = 0;
    cmd_exp[0] = "export";
    cmd_exp[2] = NULL;
    if (!ft_strncmp("cd", cmd[0], 2) && ft_strlen(cmd[0]) == 2)
    {
        if (cmd[1] && (!ft_strncmp("~", cmd[1], 1) && ft_strlen(cmd[1]) == 1))
        {
            adr = get_tilda();
            answer = chdir(adr);
            free(adr);
        }
        else if (!cmd[1])
        {
            while (envi && ft_strncmp("HOME=", envi->str, 5))
                envi = envi->next;
            if (envi)
                answer = chdir(&envi->str[5]);
            if (!envi)
            {
                ft_putstr_fd("bash: cd: HOME not set\n", 1);
                ret = 1;
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
        free(cmd_exp[1]);
    }
    return(ret);
}