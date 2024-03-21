/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:39:13 by susajid           #+#    #+#             */
/*   Updated: 2024/03/25 11:18:35 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	replace_enviornment_variable(char **cmd_arg, size_t variable_index);

void	expand_cmd_arg(char **cmd_arg)
{
	size_t	i;
	char	encloser;

	i = 0;
	encloser = 0;
	while ((*cmd_arg)[i])
	{
		if ((*cmd_arg)[i] == '"' || (*cmd_arg)[i] == '\'')
		{
			if (!encloser)
				encloser = (*cmd_arg)[i];
			else if ((*cmd_arg)[i] == encloser)
				encloser = 0;
			ft_strlcpy(*cmd_arg + i, *cmd_arg + i + 1, ft_strlen(*cmd_arg + i));
		}
		if (encloser != '\'' && (*cmd_arg)[i] == '$')
			i += replace_enviornment_variable(cmd_arg, i);
		else
			i++;
	}
}

/*
	Regex for enviornment variable identifier: [a-zA-Z_]+[a-zA-Z0-9_]*
	Function steps: (1) find the identifier string that follows the regex
					(2) get the identifier's value
					(3) replace it with the enviornment variable value
					(4) return the number of characters replaced
*/
size_t	replace_enviornment_variable(char **cmd_arg, size_t variable_index)
{
	size_t	len;
	char	*start;
	char	*temp1;
	char	*temp2;
	char	*env_value;

	start = *cmd_arg + variable_index + 1;
	while (*start == '=')
		start++;
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	if (len == 0)
		return (1);
	temp1 = ft_substr(start, 0, len);
	env_value = getenv(temp1);
	free(temp1);
	temp1 = ft_substr(*cmd_arg, 0, variable_index);
	temp2 = ft_strjoin(temp1, env_value);
	free(temp1);
	temp1 = temp2;
	temp2 = ft_strjoin(temp2, start + len);
	free(*cmd_arg);
	*cmd_arg = temp2;
	return (free(temp1), ft_strlen(env_value));
}
