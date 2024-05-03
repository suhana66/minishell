/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/03 08:14:02 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token **token_list, int *err)
{
	t_cmd	*cmd_table;
	t_cmd	*node;

	if ((*token_list)->type == PIPE)
		return (type_error(PIPE), *err = 1, NULL);
	cmd_table = NULL;
	while (*token_list)
	{
		node = cmd_new(token_list, err);
		if (*err)
			return (cmd_clear(&cmd_table), NULL);
		cmd_addback(&cmd_table, node);
		// delete pipe
	}
	return (cmd_table);
}

t_token	*cmd_redirects(t_token **token_list, int *err)
{
	t_token	*result;
	t_token	*node;
	t_token	*token;

	token = *token_list;
	while (token && !token->type)
		token = token->next;
	while (token && token->type != PIPE)
	{
		if (!token->next)
			return (token_clear(&result), type_error(0), *err = 1, NULL);
		if (token->next->type)
			return (token_clear(&result), type_error(token->next->type), *err = 1, NULL);
		if (token->type == GREAT || token->type == GREATGREAT || token->type == LESS || token->type == LESSLESS)
		{
			node = token_new(ft_strdup(token->next->str), token->type);
			if (!node)
				return (token_clear(&result), ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
			token_addback(&result, node);
			// delete two nodes
		}
	}
	return (result);
}

void	type_error(t_type type)
{
	char	*token_name;

	token_name = "";
	if (type == GREAT)
		token_name = ">";
	else if (type == GREATGREAT)
		token_name = ">>";
	else if (type == LESS)
		token_name = "<";
	else if (type == LESSLESS)
		token_name = "<<";
	else if (type == PIPE)
		token_name = "|";
	else
		token_name = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putstr_fd(token_name, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
