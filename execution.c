/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:16:39 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/21 13:12:47 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_wait(int *pid, int pipe_n)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipe_n)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	return (get_exit_status(status));
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

int	ft_fork(t_info *info, int end[2], int fd_in, t_cmd *cmd)
{
	static int	i = 0;

	if (info->reset == true)
	{
		i = 0;
		info->reset = false;
	}
	info->pid[i] = fork();
	if (info->pid[i] < 0)
	{
		ft_putstr_fd("Failed to fork\n", 2);
		reset_info(info);
	}
	if (info->pid[i] == 0)
		dup_cmd(cmd, info, end, fd_in);
	i++;
	return (0);
}

int	check_fd_heredoc(t_info *info, int end[2], t_cmd *cmd)
{
	int	fd_in;

	if (info->here_doc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_f_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

t_cmd	*ft_simple_cmdsfirst(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->prev != NULL)
	{
		cmd = cmd->prev;
	}
	return (cmd);
}

int	many_cmd_executor(t_info *info)
{
	int		end[2];
	int		fd_in;

	fd_in = 0;
	while (info->cmd_table)
	{
		//info->cmd_table = call_expander(info, info->cmd_table);
		if (info->cmd_table->next)
			pipe(end);
		send_heredoc(info, info->cmd_table);
		ft_fork(info, end, fd_in, info->cmd_table);
		close(end[1]);
		if (info->cmd_table->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(info, end, info->cmd_table);
		if (info->cmd_table->next)
			info->cmd_table = info->cmd_table->next;
		else
			break ;
	}
	info->exit_status = pipe_wait(info->pid, info->pip_n);
	info->cmd_table = ft_simple_cmdsfirst(info->cmd_table);
	return (0);
}
