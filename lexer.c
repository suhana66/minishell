/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:54:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/03 08:05:47 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
t_token	*lexer(char *input, int *err)
{
	t_token	*token_list;
	t_token	*node;
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
			if (*err)
				return (token_clear(&token_list), NULL);
		}
		node = token_new(str, type);
		if (!node)
			return (free(str), token_clear(&token_list), ft_putendl_fd(MEM_ERR_MSG, STDERR_FILENO), *err = -1, NULL);
		token_addback(&token_list, node);
	}
	return (token_list);
}

t_token	*token_new(char *str, t_type type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->str = str;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	token_addback(t_token **tokens, t_token *node)
{
	t_token	*temp;

	if (!tokens || !node)
		return ;
	if (!*tokens)
	{
		*tokens = node;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
}

void	token_delone(t_token **token)
{
	t_token	*to_delete;

	if (!token)
		return ;
	to_delete = *token;
	if ((*token)->prev)
		(*token)->prev->next = (*token)->next;
	else
		*token = (*token)->next;
	free((*token)->str);
	free(*token);
}

void	token_clear(t_token **tokens)
{
	if (!tokens)
		return ;
	while (*tokens)
		token_delone(tokens);
	*tokens = NULL;
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
