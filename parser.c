/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 12:56:54 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_list **token_list, int *err)
{
	t_list	*cmd_table;
	t_cmd	*node;

	if (((t_token *)((*token_list)->content))->type == PIPE)
		return (type_error(PIPE), *err = 1, NULL);
	cmd_table = NULL;
	while (*token_list)
	{
		node = cmd_new(token_list, err);
		if (!node)
			return (ft_lstclear(&cmd_table, cmd_del), NULL);
		*token_list = (*token_list)->next;
	}
	return (cmd_table);
}

t_cmd	*cmd_new(t_list **token_list, int *err)
{
	t_cmd	*result;

	result = (t_cmd *)malloc(sizeof(t_cmd));
	if (!result)
		return (ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
	result->redirects = NULL;
	(void)token_list;
	return (result);
	// errcode = redirects(token_list, &node->redirects);
	// 	if (errcode)
	// 		return (ft_lstclear(&cmd_table, cmd_del), cmd_del(node), errcode);
}

void	cmd_del(void *simple_cmd)
{
	ft_lstclear(&((t_cmd *)(simple_cmd))->redirects, token_del);
	free(simple_cmd);
}

// int	redirects(t_list **token_list, t_list **redirects)
// {
// 	t_list	*token_i;
// 	t_type	token_type;

// 	(void)redirects;
// 	token_i = *token_list;
// 	while (1)
// 	{
// 		while (token_i && !((t_token *)(token_i->content))->type)
// 			token_i = token_i->next;
// 		token_type = ((t_token *)(token_i->content))->type;
// 		if (!token_i->next)
// 			return (parser_type_error(0), 1);
// 		if (((t_token *)(token_i->next->content))->type)
// 			return (parser_type_error(((t_token *)(token_i->next->content))->type), 1);
// 		if (token_type == GREAT || token_type == GREATGREAT || token_type == LESS || token_type == LESSLESS)
// 		{
// 		}
// 	}
// 	return (0);
// }

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
