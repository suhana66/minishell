#include "minishell.h"

int	here_doc(t_token *heredoc, bool quotes, t_info *info, char *f_name, int stop_hd)
{
	int		fd;
	char	*line;

	fd = open(f_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str))
		&& !stop_hd)
	{
		if (quotes == false)
			//line = expander_str(info, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (stop_hd || !line)
		return (1);
	close(fd);
	return (0);
}

int	ft_heredoc(t_info *info, t_token *heredoc, char *f_name)
{
	bool	quotes;
	int		sl;
    int     stop_hd;

	sl = 0;
	if ((heredoc->str[0] == '\"'
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\"')
		|| (heredoc->str[0] == '\''
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	del_quotes(heredoc->str, '\"');
	del_quotes(heredoc->str, '\'');
	stop_hd = 0;
	// g_global.in_heredoc = 1;
	sl = here_doc(heredoc, quotes, info, f_name, stop_hd);
	//g_global.in_heredoc = 0;
	//info->heredoc = true;
	return (sl);
}

char	*heredoc_temp_file(void)
{
	static int	i = 0;
	char		*n;
	char		*f_name;

	n = ft_itoa(i++);
	f_name = ft_strjoin("build/.tmp_hdoc_file_", n);
	free(n);
	return (f_name);
}

int	send_heredoc(t_info *info, t_cmd *cmd)
{
	t_token	*start;
	int		sl;
    int     error_num

	start = cmd->redirects;
	sl = 0;
	while (cmd->redirects)
	{	
		if (cmd->redirects->type == LESSLESS)
		{
			if (cmd->hd_f_name)
				free(cmd->hd_f_name);
			cmd->hd_f_name = heredoc_temp_file();
			sl = ft_heredoc(info, cmd->redirects, cmd->hd_f_name);
			if (sl)
			{
				error_num = 1;
				return (reset_info(info));
			}
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (0);
}

int main() {
    // Create a sample t_info structure
    t_info info;
    info.envv = NULL; // Initialize envv with appropriate values

    // Create a sample t_cmd structure with redirects
    t_cmd cmd;
    cmd.argv = (char *[]){"command", NULL}; // Example argv array
    cmd.redirects = malloc(sizeof(t_token));
    if (cmd.redirects == NULL) {
        perror("Memory allocation failed");
        return (1);
    }
    cmd.redirects->type = LESSLESS; // Example redirect type
    cmd.redirects->str = "EOF"; // Example redirect string
    cmd.redirects->prev = NULL;
    cmd.redirects->next = NULL;
    cmd.builtin = NULL; // Example builtin function

    // Call the send_heredoc function
    int result = send_heredoc(&info, &cmd);
    if (result != 0) {
        printf("send_heredoc failed\n");
        // Handle error condition
    } else {
        printf("send_heredoc succeeded\n");
        // Proceed with further execution
    }

    // Free dynamically allocated memory
    free(cmd.redirects);

    return EXIT_SUCCESS;
}