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
	//free_arr(arr);
	strs = ft_split(joined_str, ' ');
	free(joined_str);
	// if neccessary remove the commend below
	// joined_str = join_split_str(strs, NULL);
	// free_arr(strs);
	// strs = ft_split(joined_str, ' ');
	// free(joined_str);
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
    // int error_num;

	if (expander(cmd, info->env))
	{
		ft_putstr_fd("memory error: unable to assign memory\n", 2);
		reset_info(info);
		return ;
	}
	if (cmd->builtin == mini_cd || cmd->builtin == mini_exit
		|| cmd->builtin == mini_export || cmd->builtin == mini_unset)
	{
		g_exit_status = cmd->builtin(info, cmd);
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
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

// #include "minishell.h" // Include your header file here

// int main(int ac, char **av, char **env) {
//     // Initialize necessary variables or data structures
//     t_info info;
//     // Assuming you have initialized the 'info' structure and its members appropriately

// 	info.env_arr = env;
// 	parse_env(&info, env);
//     // Example command to test
//     t_cmd cmd;
//     cmd.argv = malloc(sizeof(char *) * 2);
//     cmd.argv[0] = strdup("ls"); // Example command name
//     cmd.argv[1] = NULL; // NULL terminator
//     cmd.builtin = NULL; // Assuming no built-in command

//     // Call the single_cmd function to execute the command
//     single_cmd(&cmd, &info);

//     // After single_cmd returns, you can check its behavior, e.g., whether it executed the command successfully

//     // Free allocated memory
//     free(cmd.argv[0]);
//     free(cmd.argv);

//     return 0;
// }

//need to check after combining