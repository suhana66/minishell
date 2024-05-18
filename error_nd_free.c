#include "minishell.h"

int	reset_info(t_info *info, t_cmd *cmds)
{
	ft_simple_cmdsclear(&cmds);
	if (info->pid)
		free(info->pid);
	free_arr(info->path);
	implement_info(info);
	info->reset = true;
	minishell_loop(info);
	return (1);
}
