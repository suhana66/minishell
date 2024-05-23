/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:30:25 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/23 19:44:05 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_exit(t_info *info, int exit_code)
{
	array_clear(info->path);
	array_clear(info->env);
	free(info->pwd);
	free(info->old_pwd);
	cmd_clear(&info->cmd_table);
	if (info->pip_n)
		free(info->pid);
	exit(exit_code);
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

int	get_exit_status(int cmd_status)
{
	if (WIFEXITED(cmd_status))
		return (WEXITSTATUS(cmd_status));
	else if (g_recv_sig == SIGINT)
		return (g_recv_sig = 0, 130);
	else if (g_recv_sig == SIGQUIT)
		return (g_recv_sig = 0, 131);
	return (0);
}

void	dup_cmd(t_cmd *cmd, t_info *info, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, 0) < 0)
	{
		ft_putstr_fd("Failed to create pipe\n", 2);
		reset_info(info);
	}
	close(end[0]);
	if (cmd->next && dup2(end[1], 1) < 0)
	{
		ft_putstr_fd("Failed to create pipe\n", 2);
		reset_info(info);
	}
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, info);
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
