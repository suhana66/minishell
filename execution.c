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
	if (WIFEXITED(status))
	 	return(WEXITSTATUS(status));
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

// int main(int ac, char **av, char **env) {
//     // Initialize necessary variables or data structures
//     t_info info;
// 	(void) av;
// 	(void) ac;
//     // Assuming you have initialized the 'info' structure and its members appropriately
//     info.env_arr = NULL; // Example initialization
//     info.path = NULL; // Example initialization
//     info.pwd = NULL; // Example initialization
//     info.old_pwd = NULL; // Example initialization
//     parse_env(&info, env); // Example initialization
//     info.cmd_table = NULL; // Example initialization
//     info.pid = NULL; // Example initialization
//     info.pip_n = 2; // Example initialization
// 	info.here_doc = 0;

// 	info.pid = ft_calloc(sizeof(int), info.pip_n + 2);
//     // Example commands to test
//     t_cmd cmd1, cmd2, cmd3;
//     // Initialize cmd1
//     cmd1.argv = malloc(sizeof(char *) * 3);
//     cmd1.argv[0] = strdup("ls"); // Example command name
//     cmd1.argv[1] = NULL; // NULL terminator
//     cmd1.argv[2] = NULL; // NULL terminator
//     cmd1.builtin = NULL; // Assuming no built-in command
// 	cmd1.redirects = NULL;
// 	// cmd1.redirects->type = NULL; // Example redirect type
//     // cmd1.redirects->str = NULL; // Example redirect string
//     // cmd1.redirects->prev = NULL;
//     // cmd1.redirects->next = NULL;
//     cmd1.prev = NULL; // No previous command
//     cmd1.next = &cmd2; // Next command
//     // Initialize cmd2
//     cmd2.argv = malloc(sizeof(char *) * 3);
//     cmd2.argv[0] = strdup("wc"); // Example command name
//     cmd2.argv[1] = NULL; // NULL terminator
//     cmd2.argv[2] = NULL; // NULL terminator
//     cmd2.builtin = NULL; // Assuming no built-in command
// 	cmd2.redirects = NULL;
// 	// cmd2.redirects->type = NULL; // Example redirect type
//     // cmd2.redirects->str = NULL; // Example redirect string
//     // cmd2.redirects->prev = NULL;
//     // cmd2.redirects->next = NULL;
//     cmd2.prev = &cmd1; // Previous command
//     cmd2.next = &cmd3; // Next command
//     // Initialize cmd3
//     cmd3.argv = malloc(sizeof(char *) * 3);
//     cmd3.argv[0] = strdup("cat"); // Example command name
//     cmd3.argv[1] = NULL; // NULL terminator
//     cmd3.argv[2] = NULL; // NULL terminator
// 	cmd3.redirects = NULL;
// 	// cmd3.redirects->type = NULL; // Example redirect type
//     // cmd3.redirects->str = NULL; // Example redirect string
//     // cmd3.redirects->prev = NULL;
//     // cmd3.redirects->next = NULL;
//     cmd3.builtin = NULL; // Assuming no built-in command
//     cmd3.prev = &cmd2; // Previous command
//     cmd3.next = NULL; // No next command

//     // Call the many_cmd_executor function to execute the commands
//     many_cmd_executor(&info, &cmd1);

//     // After many_cmd_executor returns, you can check its behavior, e.g., whether it executed the commands successfully

//     // Free allocated memory for command arguments
//     free(cmd1.argv[0]);
//     free(cmd1.argv);
//     free(cmd2.argv[0]);
//     free(cmd2.argv);
//     free(cmd3.argv[0]);
//     free(cmd3.argv);

//     return 0;
// }