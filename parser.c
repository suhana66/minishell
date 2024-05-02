/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 14:39:53 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_list **token_list, int *err)
{
	t_list	*cmd_table;
	t_list	*node;

	if (((t_token *)((*token_list)->content))->type == PIPE)
		return (type_error(PIPE), *err = 1, NULL);
	cmd_table = NULL;
	while (*token_list)
	{
		node = cmd_new(token_list, err);
		if (*err)
			return (ft_lstclear(&cmd_table, cmd_del), NULL);
		ft_lstadd_back(&cmd_table, node);
		// delete pipe
	}
	return (cmd_table);
}

t_list	*cmd_new(t_list **token_list, int *err)
{
	t_cmd	*content;
	t_list	*node;

	content = (t_cmd *)malloc(sizeof(t_cmd));
	if (!content)
		return (ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
	content->redirects = cmd_redirects(token_list, err);
	if (err)
		return (free(content), NULL);
	// TODO
	node = ft_lstnew(content);
	if (!node)
		return (cmd_del(content), NULL);
	return (node);
}

void	cmd_del(void *simple_cmd)
{
	ft_lstclear(&((t_cmd *)(simple_cmd))->redirects, token_del);
	free(simple_cmd);
}

t_list	*cmd_redirects(t_list **token_list, int *err)
{
	t_list	*result;
	t_list	*node;
	t_token	*token;
	t_token	*token_next;
	t_list	*temp;

	temp = *token_list;
	while (temp && !((t_token *)(temp->content))->type)
		temp = temp->next;
	token = ((t_token *)(temp->content));
	token_next = ((t_token *)(temp->next->content));
	while (temp && token->type != PIPE)
	{
		if (!temp->next)
			return (ft_lstclear(&result, token_del), type_error(0), *err = 1, NULL);
		if (token_next->type)
			return (ft_lstclear(&result, token_del), type_error(token_next->type), *err = 1, NULL);
		if (token->type == GREAT || token->type == GREATGREAT || token->type == LESS || token->type == LESSLESS)
		{
			node = token_new(ft_strdup(token_next->str), token->type);
			if (!node)
				return (ft_lstclear(&result, token_del), ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
			ft_lstadd_back(&result, node);
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
