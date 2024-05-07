#include "../minishell.h"

int  build_exit(t_info *info, t_simple_cmd *simple_cmd)
{

    ft_putendl_fd("exit", 2);
    if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	str = ft_arrdup(simple_cmd->str);
	free_tools(tools);
	determine_exit_code(str);
	return (EXIT_SUCCESS);
}