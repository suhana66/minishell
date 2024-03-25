/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/03/25 12:12:38 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_length(char **input, char *delimiters, char *enclosers);
size_t	get_token_count(char *str, char *delimiters, char *enclosers);

char	**split_cli_input(char *input, char *delimiters, char *enclosers)
{
	char	**cmd_argv;
	size_t	cmd_argc;
	size_t	i;
	size_t	token_len;

	cmd_argc = get_token_count(input, delimiters, enclosers);
	cmd_argv = malloc(sizeof(char *) * (cmd_argc + 1));
	if (!cmd_argv)
		return (NULL);
	cmd_argv[cmd_argc] = NULL;
	i = 0;
	while (*input && i < cmd_argc)
	{
		while (*input && ft_strchr(delimiters, *input))
			input++;
		token_len = get_token_length(&input, delimiters, enclosers);
		cmd_argv[i] = ft_substr(input - token_len, 0, token_len);
		if (!cmd_argv[i++])
		{
			while (--i >= 0)
				free(cmd_argv[i]);
			return (free(cmd_argv), NULL);
		}
	}
	return (cmd_argv);
}

size_t	get_token_length(char **input, char *delimiters, char *enclosers)
{
	char	*token_i;
	char	encloser;
	size_t	result;

	token_i = *input;
	encloser = 0;
	while (!ft_strchr(delimiters, *token_i) || encloser)
	{
		if (!encloser && ft_strchr(enclosers, *token_i))
			encloser = *token_i;
		else if (encloser && *token_i == encloser)
			encloser = 0;
		token_i++;
	}
	result = token_i - *input;
	*input += result;
	return (result);
}

size_t	get_token_count(char *input, char *delimiters, char *enclosers)
{
	size_t	count;
	size_t	token_len;

	count = 0;
	while (1)
	{
		while (*input && ft_strchr(delimiters, *input))
			input++;
		token_len = get_token_length(&input, delimiters, enclosers);
		if (token_len == 0)
			break ;
		count++;
	}
	return (count);
}
