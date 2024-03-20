/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/03/20 14:36:34 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_length(char *input, char *delimiters, char *enclosers);
size_t	get_token_count(char *str, char *delimiters, char *enclosers);
char	**check_mallocs(char **array, size_t arrlen);

char	**split_cli_input(char *input, char *delimiters, char *enclosers)
{
	char	**cmd_argv;
	size_t	cmd_argc;
	size_t	i;
	size_t	token_len;

	if (!input || !*input)
		return (NULL);
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
		token_len = get_token_length(input, delimiters, enclosers);
		cmd_argv[i++] = ft_substr(input, 0, token_len);
		input += token_len;
	}
	return (check_mallocs(cmd_argv, cmd_argc));
}

size_t	get_token_length(char *input, char *delimiters, char *enclosers)
{
	char	*token_i;
	char	encloser;

	token_i = input;
	encloser = 0;
	while (!ft_strchr(delimiters, *token_i) || encloser)
	{
		if (!encloser && ft_strchr(enclosers, *token_i))
			encloser = *token_i;
		else if (encloser && *token_i == encloser)
			encloser = 0;
		token_i++;
	}
	return (token_i - input);
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
		token_len = get_token_length(input, delimiters, enclosers);
		if (token_len == 0)
			break ;
		count++;
		input += token_len;
	}
	return (count);
}

char	**check_mallocs(char **array, size_t arrlen)
{
	size_t	i;

	i = 0;
	while (i < arrlen)
	{
		if (!array[i])
		{
			i = 0;
			while (i < arrlen)
				free(array[i++]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}
