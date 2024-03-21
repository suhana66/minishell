/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:39:13 by susajid           #+#    #+#             */
/*   Updated: 2024/03/21 10:40:18 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_arg(char **cmd_arg)
{
	size_t	i;
	char	encloser;

	i = 0;
	encloser = 0;
	while ((*cmd_arg)[i])
	{
		if ((*cmd_arg)[i] == '"' || (*cmd_arg)[i] == '\'')
		{
			if (!encloser)
				encloser = (*cmd_arg)[i];
			else if ((*cmd_arg)[i] == encloser)
				encloser = 0;
			ft_strlcpy(*cmd_arg + i, *cmd_arg + i + 1, ft_strlen(*cmd_arg + i));
		}
		i++;
	}
}

// [a-zA-Z_]+[a-zA-Z0-9_]*
