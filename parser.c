/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/05 10:15:00 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token **token_list, int *err)
{
	t_cmd	*cmd_table;
	t_cmd	*node;
	t_token	*redirects;
	char	**argv;

	if ((*token_list)->type == PIPE)
		return (type_error(PIPE), *err = 1, NULL);
	cmd_table = NULL;
	while (*token_list)
	{
		redirects = cmd_redirects(token_list, err);
		if (*err)
			return (cmd_clear(&cmd_table), NULL);
		argv = cmd_argv(token_list);
		if (!argv)
			return (cmd_clear(&cmd_table), ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), token_clear(&redirects), *err = -1, NULL);
		node = cmd_new(argv, redirects);
		if (!node)
			return (cmd_clear(&cmd_table), ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), token_clear(&redirects), array_clear(argv), *err = -1, NULL);
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
	t_token	*head;

	token = *token_list;
	head = *token_list;
	result = NULL;
	while (1)
	{
		while (token && !token->type)
			token = token->next;
		if (!token || token->type == PIPE)
			break ;
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
			if (token == head)
				head = token->next->next;
			token_delone(&token);
			token_delone(&token);
		}
	}
	*token_list = head;
	return (result);
}

char	**cmd_argv(t_token **token_list)
{
	size_t	argc;
	char	**result;
	size_t	i;

	argc = arg_count(*token_list);
	result = (char **)malloc((argc + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[argc] = NULL;
	i = 0;
	while (i < argc)
	{
		result[i] = ft_strdup((*token_list)->str);
		if (!result[i++])
			return (array_clear(result), NULL);
		token_delone(token_list);
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

size_t	arg_count(t_token *tokens)
{
	size_t	result;

	result = 0;
	while (tokens && tokens->type != PIPE)
	{
		result++;
		tokens = tokens->next;
	}
	return (result);
}
