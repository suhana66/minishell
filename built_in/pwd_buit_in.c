#include "minishell.h"

int built_pwd(t_info *info, t_cmd *simple_cmd)
{
	(void)simple_cmd;
	ft_putendl_fd(info->pwd, 1);
	return (0);
}

// int built_pwd(t_info *info)
// {
//     char    c[1024];
//     (void) info;
//     if (getcwd(c, 1024))
//     {
//         ft_putendl_fd(c, 1);
//         return(0);
//     }
//     else
//         return (1);
// }

// int main (int av, char *ac, char **env)
// {
//     (void) av;
//     (void) ac;
//     t_info  info;

//     // ft_putstr_fd("hello", 1);
//     env_st(&info,env);
// 	f_pwd(&info);
//     //mini_pwd(&info);
//     built_pwd(&info);
// }