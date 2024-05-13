#include "../minishell.h"

int	here_doc(t_token *heredoc, bool quotes, t_info *info, char *f_name)
{
	int		fd;
	char	*line;

	fd = open(f_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str)))
	{
		//if (quotes == false) if quotes of delimiter is false we should expand it
			//line = expander_str(info, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (!line)
		return (1);
	close(fd);
	return (0);
}

char	*del_quotes(char *str, char c)
{
	int		i;
	int		len;
	char	*result;
	int		result_index;
	int		inside_quote;

	i = 0;
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	result_index = 0;
	inside_quote = 0;
	while (str[i])
	{
		if (str[i] == c && i > 0 && str[i - 1] == '=')
		{
			i++;
			inside_quote = 1;
		}
		else if (str[i] == c && inside_quote)
		{
			i++;
			inside_quote = 0;
		}
		else
		{
			result[result_index++] = str[i++];
		}
	}
	result[result_index] = '\0';
	return (result);
}



int	ft_heredoc(t_info *info, t_token *heredoc, char *f_name)
{
	bool	quotes;
	int		sl;

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
	// g_global.in_heredoc = 1;
	sl = here_doc(heredoc, quotes, info, f_name);
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
	f_name = ft_strjoin(".tmp_hdoc_file_", n);
	free(n);
	return (f_name);
}

int	send_heredoc(t_info *info, t_cmd *cmd)
{
	t_token	*start;
	int		sl;
    int     error_num;
	char	*f_name;

	start = cmd->redirects;
	sl = 0;
	while (cmd->redirects)
	{	
		if (cmd->redirects->type == LESSLESS)
		{
			f_name = heredoc_temp_file();
			sl = ft_heredoc(info, cmd->redirects, f_name);
			if (sl)
			{
				error_num = 1;
				//return (reset_info(info));
				return(1);
			}
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (0);
}

//After combining need to check with quotes and without also redirected to new file.

// int main() {
//     // Create a sample t_info structure
//     t_info info;
//     info.envv = NULL; // Initialize envv with appropriate values

//     // Create a sample t_cmd structure with redirects
//     t_cmd cmd;
//     cmd.argv = (char *[]){"command", NULL}; // Example argv array
//     cmd.redirects = malloc(sizeof(t_token));
//     if (cmd.redirects == NULL) {
//         perror("Memory allocation failed");
//         return (1);
//     }
//     cmd.redirects->type = LESSLESS; // Example redirect type
//     cmd.redirects->str = "hi"; // Example redirect string
//     cmd.redirects->prev = NULL;
//     cmd.redirects->next = NULL;
//     cmd.builtin = NULL; // Example builtin function

//     // Call the send_heredoc function
//     int result = send_heredoc(&info, &cmd);
//     if (result != 0) {
//         printf("send_heredoc failed\n");
//         // Handle error condition
//     } else {
//         printf("send_heredoc succeeded\n");
//         // Proceed with further execution
//     }

//     // Free dynamically allocated memory
//     free(cmd.redirects);

//     return EXIT_SUCCESS;
// }