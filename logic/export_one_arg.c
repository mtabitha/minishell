#include "../minishell.h"

int less_smbls(char *str1, char *str2)
{
    if (ft_strlen(str1) >= ft_strlen(str2))
        return (ft_strlen(str1));
    else
        return (ft_strlen (str2));
}

void    sorting_env(t_env *envi_dup)
{
    t_env *first;
    t_env *second;
    char *dup_str;

    dup_str = NULL;
    first = envi_dup;
    second = envi_dup->next;
    while (second)
    {
        if (ft_strncmp(first->str, second->str, less_smbls(first->str, second->str)) > 0)
        {
            dup_str = second->str;
            second->str = first->str;
            first->str = dup_str;
            first = envi_dup;
            second = envi_dup->next;
        }
        else
        {
            first = first->next;
            second = second->next;
        }
    }
}

void    output_sorted_env(t_env *envi, char **split_strs)
{
    int i;
    char *ptr;

    while (envi)
    {
        i = 1;
        split_strs = ft_split_str(envi->str, "=");

        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(split_strs[0], 1);
        if (split_strs[1] || has_equal(envi->str))
        {
            ft_putstr_fd("=\"", 1);
            ptr = ft_strchr(envi->str, '=');
            ptr++;
            ft_putstr_fd(ptr, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putstr_fd("\n", 1);
        i = 0;
        while (split_strs[i])
        {
            free(split_strs[i]);
            i++;
        }
        free(split_strs);
        envi = envi->next;
    }
}