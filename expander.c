/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 16:43:47 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_cmd_arg(char **cmd_arg)
{
	size_t	i;
	int		encloser;

	i = 0;
	encloser = 0;
	while ((*cmd_arg)[i])
	{
		if (shift_encloser((*cmd_arg)[i], &encloser))
		{
			ft_strlcpy(*cmd_arg + i, *cmd_arg + i + 1, ft_strlen(*cmd_arg + i));
			continue ;
		}
		if (encloser == '\'' || (*cmd_arg)[i] != '$')
			i++;
		else if (replace_enviornment_variable(cmd_arg, &i))
			return (1);
	}
	return (0);
}

/*
	Regex for enviornment variable identifier: [a-zA-Z_]+[a-zA-Z0-9_]*
	Expansion steps:	(1) find the identifier string that follows the regex
						(2) get the identifier's value
						(3) replace it with the enviornment variable value
						(4) return the number of characters replaced
*/
int	replace_enviornment_variable(char **cmd_arg, size_t *var_i)
{
	size_t	len;
	char	*start;
	char	*temp;
	char	*env;

	start = *cmd_arg + *var_i + 1;
	while (*start == '=')
		start++;
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	if (len == 0)
		return ((*var_i)++, 0);
	temp = ft_substr(start, 0, len);
	if (!temp)
		return (ft_putendl_fd("malloc() error", 2), 1);
	env = getenv(temp);
	free(temp);
	temp = malloc(sizeof(char) * (*var_i + ft_strlen(env) + ft_strlen(start + len) + 1));
	if (!temp)
		return (ft_putendl_fd("malloc() error", 2), 2);
	ft_strlcpy(temp, *cmd_arg, *var_i + 1);
	ft_strlcat(temp, env, *var_i + ft_strlen(env) + 1);
	ft_strlcat(temp, start + len, *var_i + ft_strlen(env) + ft_strlen(start + len) + 1);
	free(*cmd_arg);
	*cmd_arg = temp;
	*var_i += ft_strlen(env);
	return (0);
}
