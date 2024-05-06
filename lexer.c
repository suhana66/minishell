/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 14:46:46 by susajid          ###   ########.fr       */
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
		if (*input && ft_strchr(" \n\t", *input) && (input++, 1))
			continue ;
		node = token_add(token_type(&input), NULL, token_list);
		if (!node)
			err = -1;
		if (!err && !node->type)
			err = token_str(&input, " \n\t|<>", &node->str);
	}
	if (err)
		token_clear(token_list);
	return (err);
}

int	token_str(char **input, char *delimiters, char **result)
{
	size_t	i;
	int		encloser;
	char	*str;

	i = 0;
	encloser = 0;
	str = *input;
	while (str[i] && (!ft_strchr(delimiters, str[i]) || encloser))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!encloser)
				encloser = str[i];
			else if (str[i] == encloser)
				encloser = 0;
		}
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
