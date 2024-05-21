/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:30:25 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/21 10:51:54 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	memory_error(void)
{
	ft_putendl_fd("minishell: unable to assign memory", STDERR_FILENO);
}

void	free_info(t_info *info)
{
	array_clear(info->path);
	array_clear(info->env);
	free(info->pwd);
	free(info->old_pwd);
	cmd_clear(&info->cmd_table);
	if (info->pip_n)
		free(info->pid);
}

void	reset_info(t_info *info)
{
	cmd_clear(&info->cmd_table);
	if (info->pid)
		free(info->pid);
	array_clear(info->path);
	implement_info(info);
	info->reset = true;
	minishell_loop(info);
}

int	prepare_executor(t_info *info)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, cmd_sigint_handler);
	if (info->pip_n == 0)
		single_cmd(info->cmd_table, info);
	else
	{
		info->pid = ft_calloc(sizeof(int), info->pip_n + 2);
		if (!info->pid)
		{
			ft_putstr_fd("memory error: unable to assign memory\n", 2);
			return (reset_info(info), 1);
		}
		many_cmd_executor(info);
	}
	return (0);
}
