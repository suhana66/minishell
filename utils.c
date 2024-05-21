/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:25:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/21 11:14:18 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	get_encloser(char c, char *encloser)
{
	if ((c == '\"' || c == '\'') && (!*encloser || *encloser == c))
	{
		if (!*encloser)
			*encloser = c;
		else
			*encloser = 0;
		return (1);
	}
	return (0);
}

void	array_clear(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

size_t	count_pipes(t_token *token_list)
{
	size_t	result;

	result = 0;
	while (token_list)
	{
		if (token_list->type == PIPE)
			result++;
		token_list = token_list->next;
	}
	return (result);
}

size_t	array_len(char **array)
{
	size_t	result;

	result = 0;
	while (array[result])
		result++;
	return (result);
}

char	**array_dup(char **array, size_t size)
{
	char	**result;
	size_t	i;

	result = malloc(size * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (array[i] && i < size)
	{
		result[i] = ft_strdup(array[i]);
		if (!result[i])
		{
			while (--i < size)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	while (i < size)
		result[i++] = NULL;
	return (result);
}
int	prepare_executor(t_info *info)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, cmd_sigint_handler);
	if (info->pip_n == 0)
		single_cmd(info->cmd_table, info);
	else
	{
		info->pid = ft_calloc(sizeof(int), info->pip_n + 2);
		if (!info->pid)
		{
			ft_putendl_fd(MEMORY_ERR, STDERR_FILENO);
			reset_info(info);
			return(1);
		}
		many_cmd_executor(info);
	}
	return (0);
}
