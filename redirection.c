/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:37:09 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/21 13:17:31 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_append_outfile(t_token *redirects)
{
	int	fd;

	if (redirects->type == GREATGREAT)
		fd = open(redirects->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirects->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: infile: No such file or directory\n");
		return (1);
	}
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		printf("minishell: pipe error\n");
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	handle_outfile(t_token *redirects)
{
	int	fd;

	fd = check_append_outfile(redirects);
	if (fd < 0)
	{
		printf("minishell: outfile: Error\n");
		return (1);
	}
	if (fd > 0 && dup2(fd, 1) < 0)
	{
		printf("minishell: pipe error\n");
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	ck_redirects(t_cmd *cmd)
{
	t_token	*start;

	start = cmd->redirects;
	while (cmd->redirects)
	{
		if (cmd->redirects->type == LESS)
		{
			if (handle_infile(cmd->redirects->str))
				return (1);
		}
		else if (cmd->redirects->type == GREAT
			|| cmd->redirects->type == GREATGREAT)
		{
			if (handle_outfile(cmd->redirects))
				return (1);
		}
		else if (cmd->redirects->type == LESSLESS)
		{
			if (handle_infile(cmd->hd_f_name))
				return (1);
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (0);
}
