/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:13:22 by susajid           #+#    #+#             */
/*   Updated: 2024/05/04 15:31:45 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(t_token **token_list, int *err)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
	node->redirects = cmd_redirects(token_list, err);
	if (*err)
		return (free(node), NULL);
	// TODO
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	  cmd_addback(t_cmd **cmds, t_cmd *node)
{
	t_cmd	*temp;

	if (!cmds || !node)
		return ;
	if (!*cmds)
	{
		*cmds = node;
		return ;
	}
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
}

void	cmd_delone(t_cmd **cmd)
{
	t_cmd	*to_delete;

	if (!cmd || !*cmd)
		return ;
	to_delete = *cmd;
	*cmd = (*cmd)->next;
	if (*cmd)
		(*cmd)->prev = to_delete->prev;
	if (to_delete->prev)
		to_delete->prev->next = *cmd;
	token_clear(&to_delete->redirects);
	free(to_delete);
	// TODO
}

void	cmd_clear(t_cmd **cmds)
{
	if (!cmds)
		return ;
	while (*cmds)
		cmd_delone(cmds);
	*cmds = NULL;
}
