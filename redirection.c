/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:37:09 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/24 11:53:48 by susajid          ###   ########.fr       */
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
		ft_putendl_fd("minishell: infile: No such file or directory", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		ft_putendl_fd("minishell: pipe error", 2);
		close(fd);
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
		ft_putendl_fd("minishell: outfile: Error", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, 1) < 0)
	{
		ft_putendl_fd("minishell: pipe error", 2);
		close(fd);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	ck_redirects(t_cmd *cmd)
{
	t_token	*start;
	int		err;

	start = cmd->redirects;
	err = 0;
	while (cmd->redirects && !err)
	{
		if ((cmd->redirects->type == LESS && handle_infile(cmd->redirects->str))
			|| ((cmd->redirects->type == GREAT
					|| cmd->redirects->type == GREATGREAT)
				&& handle_outfile(cmd->redirects))
			|| (cmd->redirects->type == LESSLESS
				&& handle_infile(cmd->hd_f_name)))
			err = 1;
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	if (cmd->hd_f_name)
		unlink(cmd->hd_f_name);
	return (err);
}
