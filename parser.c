/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 10:06:13 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_list **token_list)
{
	t_list	*cmd_table;

	if (((t_token *)((*token_list)->content))->type == PIPE)
		return (parser_type_error(PIPE), ft_lstclear(token_list, token_del), 1);
	cmd_table = NULL;
	*token_list = cmd_table;
	return (0);
}

void	parser_type_error(t_type type)
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
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putstr_fd(token_name, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
