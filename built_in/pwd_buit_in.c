#include "minishell.h"

int built_pwd(t_info *info, t_cmd *simple_cmd)
{
	(void)simple_cmd;
	ft_putendl_fd(info->pwd, 1);
	return (0);
}
