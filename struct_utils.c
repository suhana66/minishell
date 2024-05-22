/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:13:22 by susajid           #+#    #+#             */
/*   Updated: 2024/05/22 22:01:30 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_add(t_cmd **cmds)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->argv = NULL;
	node->redirects = NULL;
	node->builtin = NULL;
	node->hd_f_name = NULL;
	node->prev = NULL;
	node->next = NULL;
	if (!cmds)
		return (node);
	if (!*cmds)
		return (*cmds = node, node);
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	node->prev = temp;
	temp->next = node;
	return (node);
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*to_delete;

	if (!cmds)
		return ;
	while (*cmds)
	{
		to_delete = *cmds;
		*cmds = (*cmds)->next;
		array_clear(to_delete->argv);
		token_clear(&to_delete->redirects);
		free(to_delete);
	}
	*cmds = NULL;
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
