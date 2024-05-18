#include "minishell.h"

int	reset_info(t_info *info)
{
	cmd_clear(&info->cmd_table);
	if (info->pid)
		free(info->pid);
	array_clear(info->path);
	implement_info(info);
	info->reset = true;
	// minishell_loop(info);
	return (1);
}
