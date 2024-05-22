/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:30:36 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/20 11:54:00 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_env(t_info *info)
{
	size_t	i;
	char	*temp;

	info->path = split_path_in_env(info->env);
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

int	find_pwd(t_info *info)
{
	size_t	i;

	i = 0;
	while (info->env[i])
	{
		if (!(ft_strncmp(info->env[i], "PWD=", 4)))
		{
			info->pwd = ft_strdup(info->env[i] + 4);
			if (!info->pwd)
				return (1);
		}
		else if (!(ft_strncmp(info->env[i], "OLDPWD=", 7)))
		{
			info->old_pwd = ft_strdup(info->env[i] + 7);
			if (!info->old_pwd)
				return (2);
		}
		i++;
	}
	return (0);
}

char	*env_search(char **env, char *key)
{
	size_t	i;
	char	*result;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)) && \
		*(env[i] + ft_strlen(key)) == '=')
		{
			result = env[i] + ft_strlen(key) + 1;
			if (!*result)
				return (NULL);
			else
				return (result);
		}
		i++;
	}
	return (NULL);
}
