/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:13:22 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 15:43:13 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_add(char **argv, t_token *redirects, t_cmd **cmds)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->argv = argv;
	node->redirects = redirects;
	node->next = NULL;
	if (!cmds)
		return (node);
	if (!*cmds)
		return (*cmds = node, node);
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
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

void	array_clear(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
