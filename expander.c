/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/05/19 12:13:03 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander(t_cmd *cmd, char **env)
{
	char	**argv;
	t_token	*redirects;
	size_t	i;

	argv = cmd->argv;
	i = 0;
	while (argv[i])
		if (expand_arg(&argv[i++], env))
			return (1);
	redirects = cmd->redirects;
	while (redirects)
	{
		if (redirects->type != LESSLESS)
			expand_arg(&redirects->str, env);
		redirects = redirects->next;
	}
	return (0);
}

/*
	Regex for enviornment variable identifier: [a-zA-Z_]+[a-zA-Z0-9_]*
	Expansion steps:	(1) check if special variable (skip if necessary)
						(2) find the identifier string that follows the regex
						(3) get the identifier's value
						(4) replace it with the enviornment variable value
						(5) return the number of characters replaced
*/
int	expand_arg(char **str, char **env)
{
	size_t	i;
	char	encloser;

	i = 0;
	encloser = 0;
	while ((*str)[i])
	{
		if (get_encloser((*str)[i], &encloser))
			ft_strlcpy(*str + i, *str + i + 1, ft_strlen(*str + i + 1) + 1);
		else if (encloser != '\'' && (*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?' && replace_exit_status(str, &i))
				return (2);
			else if ((*str)[i + 1] == '!' || (*str)[i + 1] == '$'
				|| (*str)[i + 1] == '@' || (*str)[i + 1] == '*'
				|| ft_isdigit((*str)[i + 1]))
				ft_strlcpy(*str + i, *str + i + 2, ft_strlen(*str + i + 2) + 1);
			else if (replace_enviornment_variable(str, &i, env))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	replace_enviornment_variable(char **str, size_t *var_i, char **env)
{
	size_t	len;
	char	*start;
	char	*temp;
	char	*env_val;
	size_t	result_size;

	start = *str + *var_i + 1;
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	if (len == 0)
		return ((*var_i)++, 0);
	temp = ft_substr(start, 0, len);
	if (!temp)
		return (1);
	env_val = env_search(env, temp);
	if (!env_val)
		env_val = "";
	free(temp);
	result_size = *var_i + ft_strlen(env_val) + ft_strlen(start + len) + 1;
	temp = malloc(sizeof(char) * result_size);
	if (!temp)
		return (2);
	ft_strlcpy(temp, *str, *var_i + 1);
	ft_strlcat(temp, env_val, result_size);
	ft_strlcat(temp, start + len, result_size);
	free(*str);
	*str = temp;
	*var_i += ft_strlen(env_val);
	return (0);
}

int	replace_exit_status(char **str, size_t *var_i)
{
	char	*result;
	size_t	result_size;
	char	*exit_str;

	exit_str = ft_itoa(g_exit_status);
	if (!exit_str)
		return (1);
	result_size = *var_i + ft_strlen(exit_str) + ft_strlen(*str + *var_i + 2) + 1;
	result = malloc(sizeof(char) * result_size);
	if (!result)
		return (free(exit_str), 2);
	ft_strlcpy(result, *str, *var_i + 1);
	ft_strlcat(result, exit_str, result_size);
	ft_strlcat(result, *str + *var_i + 2, result_size);
	free(*str);
	*str = result;
	*var_i += ft_strlen(exit_str);
	free(exit_str);
	return (0);
}

char	*env_search(char **env, char *key)
{
	size_t	i;
	char	*result;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)) && *(env[i] + ft_strlen(key)) == '=')
		{
			result = env[i] + ft_strlen(key) + 1;
			if (*result)
				return (NULL);
			else
				return (result);
		}
		i++;
	}
	return (NULL);
}
