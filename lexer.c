/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 09:39:01 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
t_token	*lexer(char *input, int *err)
{
	t_token	*token_list;
	t_token	*node;

	if (!err || *err)
		return (NULL);
	token_list = NULL;
	while (*input && !*err)
	{
		if (*input && ft_strchr(" \n\t", *input) && (input++, 1))
			continue ;
		node = token_new(token_type(&input), NULL);
		if (!node)
			*err = -1;
		else if (!node->type)
			node->str = token_str(&input, " \n\t|<>", err);
		token_addback(&token_list, node);
	}
	if (*err)
		token_clear(&token_list);
	return (token_list);
}

char	*token_str(char **input, char *delimiters, int *err)
{
	char	*str;
	size_t	i;
	int		encloser;

	i = 0;
	encloser = 0;
	while ((*input)[i] && (!ft_strchr(delimiters, (*input)[i]) || encloser))
	{
		if (((*input)[i] == '"' || (*input)[i] == '\'')
			&& (!encloser || (*input)[i] == encloser))
		{
			if (!encloser)
				encloser = (*input)[i];
			else
				encloser = 0;
		}
		i++;
	}
	if (encloser)
		return (ft_putendl_fd("syntax error: unable to locate closing quote", STDERR_FILENO), *err = 1, NULL);
	str = ft_substr(*input, 0, i);
	if (!str)
		return (*err = -1, NULL);
	*input += i;
	return (str);
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
