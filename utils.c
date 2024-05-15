/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:25:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/14 13:13:12 by susajid          ###   ########.fr       */
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
