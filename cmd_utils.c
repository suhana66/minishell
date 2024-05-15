/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:13:22 by susajid           #+#    #+#             */
/*   Updated: 2024/05/15 10:25:14 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_add(t_cmd **cmds)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	if (!cmds)
		return (node);
	if (!*cmds)
		return (*cmds = node, node);
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	node->next = NULL;
	node->argv = NULL;
	node->redirects = NULL;
	return (node);
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*to_delete;

	if (!cmds)
		return ;
	while (*cmds)
	{
		to_delete = *cmds;
		*cmds = (*cmds)->next;
		array_clear(to_delete->argv);
		token_clear(&to_delete->redirects);
		free(to_delete);
	}
	*cmds = NULL;
}
