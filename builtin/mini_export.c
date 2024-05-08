/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:37 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 17:13:57 by susajid          ###   ########.fr       */
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
	// if (ft_isdigit(str[0]))
	// 	return (1); //should print	error
	// if (str[0] == '=')
	// 	return (1); //should print	error
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || check_valid_identifier(str[i]))
			return (1); // should print	error
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
	t_env	*cur;
	char	*pos_equal;
	int		key_l;

	if (var[equal_s(var)] == '\"')
		var = del_quotes(var, '\"');
	if (var[equal_s(var)] == '\'')
		var = del_quotes(var, '\'');
	cur = info->envv;
	if (!info->envv)
		return (0);
	while (cur)
	{
		if (!(ft_strncmp(cur->key, var, ft_strlen(cur->key))))
		{
			pos_equal = ft_strchr(var, '=');
			if (pos_equal)
			{
				free(cur->key);
				free(cur->value);
				key_l = pos_equal - var;
				cur->key = malloc(key_l + 1);
				ft_strlcpy(cur->key, var, key_l + 1);
				cur->value = ft_strdup(var);
			}
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	env_add(char *var, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*new;
	t_env	*temp;
	int		k;

	if (!env)
		return (1);
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	value = ft_strdup(var);
	if (!value)
		return (1);
	k = ft_strchr(var, '=') - var;
	key = ft_strndup(var, k);
	if (!key)
		return (free(value), 1);
	temp = env;
	while (temp->next != NULL)
		temp = temp->next;
	new->key = key;
	new->value = value;
	new->next = NULL;
	temp->next = new;
	new->path = NULL;
	return (0);
}

void	print_with_q(char *str)
{
	char	*pos_e;
	char	*key;

	pos_e = ft_strchr(str, '=');
	key = ft_strndup(str, pos_e - str);
	ft_putstr_fd(key, 1);
	ft_putchar_fd('=', 1);
	ft_putchar_fd('"', 1);
	ft_putstr_fd(pos_e + 1, 1);
	ft_putendl_fd("\"", 1);
	free(key);
}

int	dec_sorted(t_env *head)
{
	char	**t;
	char	*str;
	int		i;

	str = env_to_str(head);
	t = ft_split(str, '\n');
	if (!t || !str)
		return (1);
	sort_env(t);
	i = 0;
	if (!t)
		return (1);
	while (t[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(t[i], '='))
			print_with_q(t[i]);
		else
			ft_putendl_fd(t[i], 1);
		i++;
	}
	// free array t
	return (free(str), 1);
}

int	mini_export(t_info *info, t_cmd *simple_cmd)
{
	int	i;

	if (info->envv == NULL)
		return (0);
	if (!simple_cmd->argv[1] || simple_cmd->argv[1][0] == '\0')
		dec_sorted(info->envv);
	i = 1;
	while (simple_cmd->argv[i])
	{
		if (check_param(simple_cmd->argv[i]) == 0 && !var_exist(simple_cmd->argv[i], info))
			env_add(simple_cmd->argv[i], info->envv);
		i++;
	}
	return (0);
}
