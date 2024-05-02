#include "../minishell.h"

int f_pwd(t_info *info)
{
    t_env   *t;

    t = info->envv;
    while (t)
    {
        if (!(ft_strncmp(t->value, "PWD=", 4)))
        {
            if (info->pwd == NULL)
                info->pwd = ft_substr(t->value, 4, ft_strlen(t->value) - 4);
        }
        else if (!(ft_strncmp(t->value, "OLDPWD=", 7)))
        {
            if (info->old_pwd == NULL)
                info->old_pwd = ft_substr(t->value, 4, ft_strlen(t->value) - 4);
        }
        t = t->next;
    }
    if (!info->pwd || !info->old_pwd)
        return (0);
    return (1);
}