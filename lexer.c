/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 09:16:29 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
t_lexer	*lexer(char *input)
{
	enum e_token	token_type;
	char			*str;
	t_lexer			*token_list;

	token_type = 0;
	str = NULL;
	while (*input)
	{
		if (*input == '|' && (input++, 1))
			token_type = PIPE;
		else if (*input == '>' && (input++, 1))
		{
			token_type = GREAT;
			if (*input == '>' && (input++, 1))
				token_type = GREATGREAT;
		}
		else if (*input == '<' && (input++, 1))
		{
			token_type = LESS;
			if (*input == '<' && (input++, 1))
				token_type = LESSLESS;
		}
		else if (*input && ft_strchr(" \n\t", *input) && (input++, 1))
			continue ;
		else
		{
			str = ft_substr(input, 0, lexer_token_length(&input, " \n\t|<>"));
			if (!str)
				return (ft_putendl_fd("memory error: unable to assign memory", 2), NULL);
			if (!*str)
				return (free(str), NULL);
		}
		// TODO: add node
	}
	(void)token_list;
	(void)str;
	(void)token_type;
	return (NULL);
}

size_t	lexer_token_length(char **input, char *delimiters)
{
	char	*i;
	int		encloser;
	size_t	result;

	i = *input;
	encloser = 0;
	while (*i && (!ft_strchr(delimiters, *i) || encloser))
	{
		if ((*i == '"' || *i == '\'') && (!encloser || *i == encloser))
		{
			if (!encloser)
				encloser = *i;
			else
				encloser = 0;
		}
		i++;
	}
	if (encloser)
		return (ft_putendl_fd("syntax error: unable to locate closing quote\n",
				STDERR_FILENO), 0);
	result = i - *input;
	*input += result;
	return (result);
}
