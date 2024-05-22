/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:37:38 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/22 17:56:33 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_split_str(char **str, char *new_str)
{
	char	*t;
	char	*add_space;
	int		i;

	t = ft_strdup(str[0]);
	i = 1;
	while (str[i])
	{
		new_str = t;
		add_space = ft_strjoin(new_str, " ");
		free(new_str);
		t = ft_strjoin(add_space, str[i]);
		free(add_space);
		i++;
	}
	new_str = t;
	return (new_str);
}

char	**split_again(char **arr)
{
	char	**strs;
	char	*joined_str;

	joined_str = join_split_str(arr, NULL);
	strs = ft_split(joined_str, ' ');
	free(joined_str);
	return (strs);
}

int	find_cmd(t_cmd *cmd, t_info *info)
{
	int		i;
	char	*mycmd;

	i = 0;
	cmd->argv = split_again(cmd->argv);
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
			exit(1);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(info, cmd);
		exit(exit_code);
	}
	else if (cmd->argv[0][0] != '\0')
		exit_code = find_cmd(cmd, info);
	exit(exit_code);
}

void	single_cmd(t_cmd *cmd, t_info *info)
{
	int	pid;
	int	status;

	if (expander(cmd, info))
	{
		ft_putendl_fd(MEMORY_ERR, STDERR_FILENO);
		reset_info(info);
		return ;
	}
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
