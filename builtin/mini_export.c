/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:37 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/19 13:35:41 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	equal_s(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']' || c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.' || c == ':' || c == '/' || c == '{' || c == '}' || c == '+' || c == '^' || c == '%' || c == '#' || c == '@' || c == '!' || c == '~' || c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

int	check_param(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (export_error(str));
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || check_valid_identifier(str[i]))
			return (export_error(str)); // should print	error
		i++;
	}
	return (0);
}

char	*del_quotes(char *str, char c)
{
	int		i;
	int		len;
	char	*result;
	int		result_index;
	int		inside_quote;

	i = 0;
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	result_index = 0;
	inside_quote = 0;
	while (str[i])
	{
		if (str[i] == c && i > 0 && str[i - 1] == '=')
		{
			i++;
			inside_quote = 1;
		}
		else if (str[i] == c && inside_quote)
		{
			i++;
			inside_quote = 0;
		}
		else
		{
			result[result_index++] = str[i++];
		}
	}
	result[result_index] = '\0';
	return (result);
}

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **env)
{
	size_t	i;
	size_t	env_len;
	int		ordered;
	char	*t;

	ordered = 0;
	env_len = env_size(env);
	while (env && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				t = env[i];
				env[i] = env[i + 1];
				env[i + 1] = t;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

int	var_exist(char *var, t_info *info)
{
	size_t	i;
	size_t	eq_s;

	if (var[equal_s(var)] == '\"')
		var = del_quotes(var, '\"');
	if (var[equal_s(var)] == '\'')
		var = del_quotes(var, '\'');
	if (!info->env)
		return (0);
	i = 0;
	while (info->env[i])
	{
		eq_s = equal_s(info->env[i]);
		if (eq_s == 0)
			eq_s = ft_strlen(info->env[i]);
		if (!(ft_strncmp(info->env[i], var, eq_s)))
		{
			free(info->env[i]);
			info->env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	env_add(char *var, char ***env)
{
	char	**temp;
	size_t	len;

	if (!*env)
		return (0);
	if (var[equal_s(var)] == '\"')
		var = del_quotes(var, '\"');
	if (var[equal_s(var)] == '\'')
		var = del_quotes(var, '\'');
	len = array_len(*env);
	temp = array_dup(*env, len + 2);
	if (!temp)
		return (1);
	temp[len] = ft_strdup(var);
	array_clear(*env);
	*env = temp;
	return (0);
}

void	print_with_q(char *str)
{
	char	*pos_e;
	char	*key;

	pos_e = ft_strchr(str, '=');
	key = ft_substr(str, 0, pos_e - str);
	ft_putstr_fd(key, 1);
	ft_putchar_fd('=', 1);
	ft_putchar_fd('"', 1);
	ft_putstr_fd(pos_e + 1, 1);
	ft_putendl_fd("\"", 1);
	free(key);
}

int	dec_sorted(char **env_arr)
{
	int		i;

	if (!env_arr)
		return (0);
	sort_env(env_arr);
	i = 0;
	if (!env_arr)
		return (1);
	while (env_arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(env_arr[i], '='))
			print_with_q(env_arr[i]);
		else
			ft_putendl_fd(env_arr[i], 1);
		i++;
	}
	return (1);
}

int	mini_export(t_info *info, t_cmd *simple_cmd)
{
	int		i;

	if (!info->env)
		return (0);
	if (!simple_cmd->argv[1] || simple_cmd->argv[1][0] == '\0')
		dec_sorted(info->env);
	i = 1;
	while (simple_cmd->argv[i])
	{
		if (check_param(simple_cmd->argv[i]) == 0 && !var_exist(simple_cmd->argv[i], info))
			env_add(simple_cmd->argv[i], &info->env);
		if(!ft_strncmp(simple_cmd->argv[i], "PATH=", 5))
			path_update(info);
		info->pwd = env_search(info->env, "PWD");
		info->old_pwd = env_search(info->env, "OLDPWD");
		i++;
	}
	return (0);
}
