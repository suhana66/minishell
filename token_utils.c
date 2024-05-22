/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:10:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/22 22:23:12 by susajid          ###   ########.fr       */
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
	node->prev = temp;
	temp->next = node;
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

size_t	count_pipes(t_token *token_list)
{
	size_t	result;

	result = 0;
	while (token_list)
	{
		if (token_list->type == PIPE)
			result++;
		token_list = token_list->next;
	}
	return (result);
}
