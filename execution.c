#include "minishell.h"


// t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd)
// {
// 	t_lexer	*start;

// 	cmd->str = expander(tools, cmd->str);
// 	start = cmd->redirections;
// 	while (cmd->redirections)
// 	{
// 		if (cmd->redirections->token != LESS_LESS)
// 			cmd->redirections->str
// 				= expander_str(tools, cmd->redirections->str);
// 		cmd->redirections = cmd->redirections->next;
// 	}
// 	cmd->redirections = start;
// 	return (cmd);
// }

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	// if (WIFEXITED(status))
	// 	g_global.error_num = WEXITSTATUS(status);
	return (0);
}

void	dup_cmd(t_cmd *cmd, t_info *info, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, 0) < 0)
        printf("dup not created");
		//ft_error(4, tools);
	close(end[0]);
	if (cmd->next && dup2(end[1], 1) < 0)
        printf("dup not created");
		//ft_error(4, tools);
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
        printf("child not created");
		//ft_error(5, tools);
	if (info->pid[i] == 0)
		dup_cmd(cmd, info, end, fd_in);
	i++;
	return (0);
}

int	check_fd_heredoc(t_info *info, int end[2], t_cmd *cmd)
{
	int	fd_in;

	if (info->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

t_cmd	*ft_simple_cmdsfirst(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd->prev != NULL)
	{
		cmd = cmd->prev;
		i++;
	}
	return (cmd);
}

int	many_cmd_executor(t_info *info, t_cmd *cmds)
{
	int		end[2];
	int		fd_in;

	fd_in = 0;
	while (cmds)
	{
		//cmds = call_expander(tools, cmds);
		if (cmds->next)
			pipe(end);
		send_heredoc(info, cmds);
		ft_fork(info, end, fd_in, cmds);
		close(end[1]);
		if (cmds->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(info, end, cmds);
		if (cmds->next)
			cmds = cmds->next;
		else
			break ;
	}
	pipe_wait(info->pid, info->pipes);
	cmds = ft_simple_cmdsfirst(cmds);
	return (0);
}