/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:23:50 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/21 13:14:23 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_token *heredoc, bool quotes, t_info *info, char *f_name)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(f_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	len = ft_strlen(heredoc->str);
	while (1)
	{
		line = readline(HEREDOC_MSG);
		if (quotes == false)
			parse_arg(&line, info, false, true);
		if (!line || (ft_strlen(line) == len && !ft_strncmp(heredoc->str, line, len)) || g_recv_sig)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (!line || g_recv_sig)
		return (1);
	close(fd);
	(void)quotes;
	(void)info;
	return (0);
}

int	ft_heredoc(t_info *info, t_token *heredoc, char *f_name)
{
	bool	quotes;
	int		sl;

	sl = 0;
	if (ft_strchr(heredoc->str, '\"') || ft_strchr(heredoc->str, '\''))
		quotes = true;
	else
		quotes = false;
	parse_arg(&heredoc->str, info, true, false);
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	sl = here_doc(heredoc, quotes, info, f_name);
	signal(SIGINT, cmd_sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	info->here_doc = true;
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
				info->exit_status = 1;
				g_recv_sig = 0;
				return (reset_info(info), 1);
			}
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (0);
}
