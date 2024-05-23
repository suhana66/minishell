/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:13:22 by susajid           #+#    #+#             */
/*   Updated: 2024/05/23 06:31:05 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
