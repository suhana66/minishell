/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:08 by susajid           #+#    #+#             */
/*   Updated: 2024/05/22 21:54:03 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander(t_cmd *cmd, t_info *info)
{
	char	**argv;
	t_token	*redirects;
	size_t	i;

	argv = cmd->argv;
	i = 0;
	while (argv[i])
		if (parse_arg(&argv[i++], info, true, true))
			return (1);
	redirects = cmd->redirects;
	while (redirects)
	{
		if (redirects->type != LESSLESS)
			parse_arg(&redirects->str, info, true, true);
		redirects = redirects->next;
	}
	return (0);
}

/*
	Regex for enviornment variable identifier: [a-zA-Z_]+[a-zA-Z0-9_]*
	Expansion steps:	(1) check if special variable
						(2) find the identifier string that follows the regex
						(3) get the identifier's value
						(4) replace it with the enviornment variable value
						(5) return the number of characters replaced
*/
int	parse_arg(char **str, t_info *info, bool if_del_quotes, bool if_expand)
{
	size_t	i;
	char	encloser;

	i = 0;
	encloser = 0;
	while ((*str)[i])
	{
		if (if_del_quotes && get_encloser((*str)[i], &encloser))
			ft_strlcpy(*str + i, *str + i + 1, ft_strlen(*str + i + 1) + 1);
		else if (if_expand && encloser != '\'' && (*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?' && \
			replace_exit_status(str, &i, info->exit_status))
				return (2);
			else if (replace_enviornment_variable(str, &i, info->env))
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
	char	*key;
	char	*env_val;

	start = *str + *var_i + 1;
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	if (ft_isdigit(start[0]) || len == 0)
		return ((*var_i)++, 0);
	key = ft_substr(start, 0, len);
	if (!key)
		return (1);
	env_val = env_search(env, key);
	if (!env_val)
		env_val = "";
	free(key);
	if (replace_str(str, var_i, len + 1, env_val))
		return (2);
	return (0);
}

int	replace_exit_status(char **str, size_t *var_i, int exit_status)
{
	char	*exit_str;

	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (1);
	if (replace_str(str, var_i, 2, exit_str))
		return (free(exit_str), 2);
	free(exit_str);
	return (0);
}

int	replace_str(char **str, size_t *start, size_t len, char *rep_val)
{
	size_t	result_size;
	char	*result;

	result_size = *start + ft_strlen(rep_val)
		+ ft_strlen(*str + *start + len) + 1;
	result = malloc(sizeof(char) * result_size);
	if (!result)
		return (EXIT_FAILURE);
	ft_strlcpy(result, *str, *start + 1);
	ft_strlcat(result, rep_val, result_size);
	ft_strlcat(result, *str + *start + len, result_size);
	free(*str);
	*str = result;
	*start += ft_strlen(rep_val);
	return (EXIT_SUCCESS);
}
