/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:37:38 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/23 17:53:42 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd(t_cmd *cmd, t_info *info)
{
	int		i;
	char	*mycmd;

	i = 0;
	if (!access(cmd->argv[0], F_OK))
		execve(cmd->argv[0], cmd->argv, info->env);
	while (info->path && info->path[i])
	{
		mycmd = ft_strjoin(info->path[i], cmd->argv[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->argv, info->env);
		free(mycmd);
		i++;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

void	handle_cmd(t_cmd *cmd, t_info *info)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirects)
		if (ck_redirects(cmd))
			process_exit(info, 1);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(info, cmd);
		process_exit(info, exit_code);
	}
	else if (cmd->argv[0][0] != '\0')
		exit_code = find_cmd(cmd, info);
	process_exit(info, exit_code);
}

void	single_cmd(t_cmd *cmd, t_info *info)
{
	int	pid;
	int	status;

	if (expander(cmd, info))
		return (ft_putendl_fd(MEMORY_ERR, STDERR_FILENO),
			(void)reset_info(info));
	if (cmd->builtin == mini_cd || cmd->builtin == mini_exit
		|| cmd->builtin == mini_export || cmd->builtin == mini_unset)
	{
		info->exit_status = cmd->builtin(info, cmd);
		return ;
	}
	send_heredoc(info, cmd);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Failed to fork\n", 2);
		reset_info(info);
	}
	if (pid == 0)
		handle_cmd(cmd, info);
	waitpid(pid, &status, 0);
	info->exit_status = get_exit_status(status);
}

t_cmd	*cmd_add(t_cmd **cmds)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->argv = NULL;
	node->redirects = NULL;
	node->builtin = NULL;
	node->hd_f_name = NULL;
	node->prev = NULL;
	node->next = NULL;
	if (!cmds)
		return (node);
	if (!*cmds)
		return (*cmds = node, node);
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	node->prev = temp;
	temp->next = node;
	return (node);
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*to_delete;

	if (!cmds)
		return ;
	while (*cmds)
	{
		to_delete = *cmds;
		*cmds = (*cmds)->next;
		array_clear(to_delete->argv);
		token_clear(&to_delete->redirects);
		free(to_delete->hd_f_name);
		free(to_delete);
	}
	*cmds = NULL;
}
