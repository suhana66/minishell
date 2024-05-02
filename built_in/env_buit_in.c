#include "../minishell.h"



int built_env(t_info *info, t_simple_cmds *simple_cmd)
{
    t_env *t;

    //(void) simple_cmd;
    if (!info->envv)
        return(1);
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

// int main (int av, char *ac, char **env)
// {
//     (void) av;
//     (void) ac;
//     t_info  info;

// 	env_st(&info,env);
//     built_env(&info);
// }