/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 12:27:20 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
t_list	*lexer(char *input, int *err)
{
	t_list	*token_list;
	t_list	*node;
	t_type	type;
	char	*str;

	while (*input)
	{
		if (*input && ft_strchr(" \n\t", *input) && (input++, 1))
			continue ;
		type = token_type(&input);
		str = NULL;
		if (!type)
		{
			str = token_str(&input, " \n\t|<>", err);
			if (!str)
				return (ft_lstclear(&token_list, token_del), NULL);
		}
		node = token_new(str, type);
		if (!node)
			return (ft_lstclear(&token_list, token_del), ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
		ft_lstadd_back(&token_list, node);
	}
	return (token_list);
}

t_list	*token_new(char *str, t_type type)
{
	t_token	*content;
	t_list	*node;

	content = (t_token *)malloc(sizeof(t_token));
	if (!content)
		return (free(str), NULL);
	content->type = type;
	content->str = str;
	node = ft_lstnew(content);
	if (!node)
		return (token_del(content), NULL);
	return (node);
}

void	token_del(void *token)
{
	free(((t_token *)token)->str);
	free(token);
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
		return (ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
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
