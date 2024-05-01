/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 08:32:14 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_list *token_list)
{
	t_list	*cmd_table;

	if (!token_list)
		return (NULL);
	if (((t_token *)(token_list->content))->type == PIPE)
		return (parser_token_error(PIPE), ft_lstclear(&token_list, token_del), NULL);
	cmd_table = NULL;
	return (cmd_table);
}

void	parser_token_error(t_type type)
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
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token_name, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
