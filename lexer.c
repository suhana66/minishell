/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 14:01:23 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
t_list	*lexer(char *input)
{
	t_list			*token_list;
	t_list			*node;
	t_token			*content;
	t_token_type	token_type;
	char			*str;

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
			str = ft_substr(input, 0, token_length(&input, " \n\t|<>"));
			if (!str)
				return (ft_perror(3), NULL);
			if (!*str)
				return (free(str), NULL);
		}
		content = (t_token *)malloc(sizeof(t_token));
		if (!content)
			return (ft_perror(3), free(str), ft_lstclear(&token_list, token_del), NULL);
		content->token_type = token_type;
		content->str = str;
		node = ft_lstnew(content);
		if (!node)
			return (ft_perror(3), token_del(content), ft_lstclear(&token_list, token_del), NULL);
		ft_lstadd_back(&token_list, node);
	}
	return (token_list);
}

void	token_del(void *token)
{
	free(((t_token *)token)->str);
	free(token);
}

size_t	token_length(char **input, char *delimiters)
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
		return (ft_perror(10), 0);
	result = i - *input;
	*input += result;
	return (result);
}
