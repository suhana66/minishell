/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/23 06:56:31 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
int	lexer(char *input, t_token **token_list)
{
	t_token	*node;
	int		err;

	*token_list = NULL;
	err = 0;
	while (*input && !err)
	{
		if (ft_strchr(" \n\t", *input) && (input++, 1))
			continue ;
		node = token_add(token_type(&input), NULL, token_list);
		if (!node)
			err = -1;
		else if (!node->type)
			err = token_str(&input, " \n\t|<>", &node->str);
	}
	return (err);
}

int	token_str(char **input, char *delimiters, char **result)
{
	size_t	i;
	char	encloser;
	char	*str;

	i = 0;
	encloser = 0;
	str = *input;
	while (str[i] && (!ft_strchr(delimiters, str[i]) || encloser))
	{
		get_encloser(str[i], &encloser);
		i++;
	}
	if (encloser)
		return (ft_putendl_fd("syntax error: unable to locate closing quote",
				STDERR_FILENO), 1);
	*result = ft_substr(*input, 0, i);
	if (!*result)
		return (-1);
	return (*input += i, 0);
}

t_type	token_type(char **input)
{
	t_type	type;

	type = 0;
	if (**input == '|' && ((*input)++, 1))
		type = PIPE;
	else if (**input == '>' && ((*input)++, 1))
	{
		type = GREAT;
		if (**input == '>' && ((*input)++, 1))
			type = GREATGREAT;
	}
	else if (**input == '<' && ((*input)++, 1))
	{
		type = LESS;
		if (**input == '<' && ((*input)++, 1))
			type = LESSLESS;
	}
	return (type);
}

char	get_encloser(char c, char *encloser)
{
	if ((c == '\"' || c == '\'') && (!*encloser || *encloser == c))
	{
		if (!*encloser)
			*encloser = c;
		else
			*encloser = 0;
		return (1);
	}
	return (0);
}

void	type_error(t_token *token)
{
	char	*token_name;

	if (!token)
		token_name = "newline";
	else if (token->type == GREAT)
		token_name = ">";
	else if (token->type == GREATGREAT)
		token_name = ">>";
	else if (token->type == LESS)
		token_name = "<";
	else if (token->type == LESSLESS)
		token_name = "<<";
	else if (token->type == PIPE)
		token_name = "|";
	else
		return ;
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putstr_fd(token_name, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
