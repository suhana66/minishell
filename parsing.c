/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/03/25 15:21:17 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_length(char **input, char *delimiters, char *enclosers);
size_t	get_token_count(char *str, char *delimiters, char *enclosers);
int		replace_enviornment_variable(char **cmd_arg, size_t *variable_index);

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

int	expand_cmd_arg(char **cmd_arg)
{
	size_t	i;
	char	encloser;

	i = 0;
	encloser = 0;
	while ((*cmd_arg)[i])
	{
		if (((*cmd_arg)[i] == '"' || (*cmd_arg)[i] == '\'')
			&& (!encloser || (*cmd_arg)[i] == encloser))
		{
			if (!encloser)
				encloser = (*cmd_arg)[i];
			else
				encloser = 0;
			ft_strlcpy(*cmd_arg + i, *cmd_arg + i + 1, ft_strlen(*cmd_arg + i));
			continue ;
		}
		if (encloser != '\'' && (*cmd_arg)[i] == '$')
		{
			if (replace_enviornment_variable(cmd_arg, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
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

/*
	Regex for enviornment variable identifier: [a-zA-Z_]+[a-zA-Z0-9_]*
	Function steps: (1) find the identifier string that follows the regex
					(2) get the identifier's value
					(3) replace it with the enviornment variable value
					(4) return the number of characters replaced
*/
int	replace_enviornment_variable(char **cmd_arg, size_t *variable_index)
{
	size_t	len;
	char	*start;
	char	*temp1;
	char	*temp2;
	char	*env_value;

	start = *cmd_arg + *variable_index + 1;
	while (*start == '=')
		start++;
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	if (len == 0)
		return ((*variable_index)++, 0);
	// TODO: ft_substr & ft_strjoin error conditions
	temp1 = ft_substr(start, 0, len);
	env_value = getenv(temp1);
	free(temp1);
	temp1 = ft_substr(*cmd_arg, 0, *variable_index);
	temp2 = ft_strjoin(temp1, env_value);
	free(temp1);
	temp1 = temp2;
	temp2 = ft_strjoin(temp2, start + len);
	free(temp1);
	free(*cmd_arg);
	*cmd_arg = temp2;
	*variable_index += ft_strlen(env_value);
	return (0);
}
