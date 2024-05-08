#include "../minishell.h"



int built_pwd(t_info *info)
{
    char    c[1024];
    (void) info;
    if (getcwd(c, 1024))
    {
        ft_putendl_fd(c, 1);
        return(0);
    }
    else
        return (1);
}
