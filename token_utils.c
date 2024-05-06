/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:10:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 15:05:41 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_add(t_type type, char *str, t_token **tokens)
{
	t_token	*node;
	t_token	*temp;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->str = str;
	node->prev = NULL;
	node->next = NULL;
	if (!tokens)
		return (node);
	if (!*tokens)
		return (*tokens = node, node);
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
	return (node);
}

void	token_delone(t_token **token)
{
	t_token	*to_delete;

	if (!token || !*token)
		return ;
	to_delete = *token;
	*token = (*token)->next;
	if (*token)
		(*token)->prev = to_delete->prev;
	if (to_delete->prev)
		to_delete->prev->next = *token;
	free(to_delete->str);
	free(to_delete);
}

void	token_clear(t_token **tokens)
{
	if (!tokens)
		return ;
	while (*tokens)
		token_delone(tokens);
	*tokens = NULL;
}
