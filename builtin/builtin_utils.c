/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:07 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/23 11:59:18 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_update(t_info *info)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	array_clear(info->path);
	if (env_search(info->env, "PATH"))
		info->path = ft_split(env_search(info->env, "PATH"), ':');
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
}

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

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
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~' || c == '=' || c == '-' || c == '?' || c == '&'
		|| c == '*');
}
