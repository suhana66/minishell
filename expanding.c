/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:39:13 by susajid           #+#    #+#             */
/*   Updated: 2024/03/21 14:10:15 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	replace_enviornment_variable(char **cmd_arg, size_t variable_index);
size_t	enviornment_variable_identifier_len(char *str);

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
	Function steps: (1) find the identifier string that follows the regex and get its value
					(2) replace it with the enviornment variable value
					(3) return the number of characters replaced
*/
size_t	replace_enviornment_variable(char **cmd_arg, size_t variable_index)
{
	size_t	identifier_len;
	char	*temp1;
	char	*temp2;
	char	*env_value;

	temp1 = *cmd_arg + variable_index + 1;
	while (*temp1 && (ft_isalnum(*temp1) || *temp1 == '_'))
		temp1++;
	identifier_len = temp1 - *cmd_arg - variable_index - 1;
	if (identifier_len == 0)
		return (1);
	temp1 = ft_substr(*cmd_arg + variable_index + 1, 0, identifier_len);
	env_value = getenv(temp1);
	free(temp1);
	temp1 = ft_substr(*cmd_arg, 0, variable_index);
	temp2 = ft_strjoin(temp1, env_value);
	free(temp1);
	temp1 = temp2;
	temp2 = ft_strjoin(temp2, *cmd_arg + variable_index + identifier_len + 1);
	free(temp1);
	temp1 = *cmd_arg;
	*cmd_arg = temp2;
	free(temp1);
	return (ft_strlen(env_value));
}
