/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 12:06:40 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmd	*parser(t_lexer *token_list)
{
	t_simple_cmd	*cmd_table;

	if (token_list->token_type == PIPE)
		return (parser_token_error(PIPE), NULL);
	cmd_table = NULL;
	return (cmd_table);
}

void parser_token_error(t_token token)
{
    char *token_str;

	token_str = "";
    if (token == GREAT)
        token_str = ">";
    else if (token == GREATGREAT)
        token_str = ">>";
    else if (token == LESS)
        token_str = "<";
    else if (token == LESSLESS)
        token_str = "<<";
    else if (token == PIPE)
        token_str = "|";
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token_str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
