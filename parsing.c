/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/03/19 18:02:29 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	word_count(char *str, char *delimiters);
char	**check_mallocs(char **array, size_t arrlen);

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
char	**parse_cli_input(char *input)
{
	char	*delimiters;
	char	**cmd_argv;
	size_t	cmd_argc;
	size_t	i;
	char	*word_i;

	if (!input || !*input)
		return (NULL);
	delimiters = " \t\n";
	cmd_argc = word_count(input, delimiters);
	cmd_argv = malloc(sizeof(char *) * (cmd_argc + 1));
	if (!cmd_argv)
		return (NULL);
	cmd_argv[cmd_argc] = NULL;
	i = 0;
	while (*input && i < cmd_argc)
	{
		while (*input && ft_strchr(delimiters, *input))
			input++;
		word_i = input;
		while (!ft_strchr(delimiters, *word_i))
			word_i++;
		cmd_argv[i++] = ft_substr(input, 0, word_i - input);
		input = word_i;
	}
	return (check_mallocs(cmd_argv, cmd_argc));
}

size_t	word_count(char *str, char *delimiters)
{
	size_t	count;
	int		counted;

	count = 0;
	counted = 0;
	while (*str)
	{
		if (ft_strchr(delimiters, *str))
			counted = 0;
		else if (!counted)
		{
			count++;
			counted = 1;
		}
		str++;
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
