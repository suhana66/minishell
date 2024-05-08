#include "minishell.h"

int built_env(t_info *info, t_cmd *simple_cmd)
{
    t_env *t;

    (void)simple_cmd;
    if (!info->envv)
        return (1);
    t = info->envv;
    if (t)
    {
        while (t)
        {
            if (ft_strchr(t->value, '='))
                printf("%s\n", t->value);
            t = t->next;
        }
        return (0);
    }
    else
        return (1);
}
