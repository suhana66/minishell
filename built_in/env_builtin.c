#include "../minishell.h"

int built_env(t_info *info, char *str)
{
    t_env *t;

    //check_nopath
    if (!info->envv || info->no_path)
        return(1);
    // also should add error no such file or directory
    if (ft_strlen(str) != 3)
        return (1);
    // also should add error command not found
    t = info->envv;
    if (t)
    {
        while(t)
        {
            if (ft_strchr(t->value, '='))
                ft_putendl_fd(t->value, 1);
            t = t->next;
        }
        return (0);
    }
    else
        return (1);
}
