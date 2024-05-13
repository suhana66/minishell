/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajidstudent.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:30:36 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/13 11:11:42 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_env(t_info *info, char **env)
{
	size_t	i;
	char	*temp;

	info->env = NULL;
	info->pwd = NULL;
	info->old_pwd = NULL;
	info->cmd_table = NULL;
	info->path = split_path_in_env(env);
	if (!info->path)
		return (1);
	i = 0;
	while (info->path[i])
	{
		if (info->path[i][ft_strlen(info->path[i]) - 1] != '/')
		{
			temp = ft_strjoin(info->path[i], "/");
			free(info->path[i]);
			info->path[i] = temp;
		}
		i++;
	}
	info->env = env_list(env);
	if (!info->env)
		return (2);
	return (0);
}

char	**split_path_in_env(char **env)
{
	size_t	i;
	char	**result;

	i = 0;
	result = NULL;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH=", 5)))
		{
			result = ft_split(env[i] + 5, ':');
			if (!result)
				return (NULL);
		}
		i++;
	}
	if (!result)
	{
		result = malloc(sizeof(char *));
		if (result)
			result[0] = NULL;
	}
	return (result);
}

t_env	*env_new(char *str)
{
	t_env	*node;
	size_t	key_l;
	char	*pos_equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	pos_equal = ft_strchr(str, '=');
	if (!pos_equal)
		return (free(node), NULL);
	key_l = pos_equal - str;
	node->key = malloc(key_l + 1);
	if (!node->key)
		return (free(node), NULL);
	ft_strlcpy(node->key, str, key_l + 1);
	node->value = ft_strdup(str);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	node->next = NULL;
	return (node);
}

t_env	*env_list(char **env)
{
	t_env	*node;
	t_env	*result;
	t_env	*temp;
	size_t	i;

	i = 0;
	result = NULL;
	while (env[i])
	{
		node = env_new(env[i]);
		if (!node)
		{
			free_env(result);
			return (NULL);
		}
		if (!result)
			result = node;
		else
			temp->next = node;
		temp = node;
		i++;
	}
	return (result);
}

void	free_env(t_env *head)
{
	t_env	*to_delete;

	while (head)
	{
		to_delete = head;
		head = head->next;
		free(to_delete->key);
		free(to_delete->value);
		free(to_delete);
	}
}
