/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:39:13 by susajid           #+#    #+#             */
/*   Updated: 2024/03/21 09:08:06 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_arg(char **cmd_arg)
{
	(void)cmd_arg;
}

// void	expand_cmd_argv(char **cmd_argv)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	encloser;

// 	i = 0;
// 	while (cmd_argv[i])
// 	{
// 		j = 0;
// 		while (cmd_argv[i][j])
// 		{
// 			encloser = 0;
// 			if (!encloser && (encloser == '"' || encloser == '\''))
// 			{
// 				encloser = cmd_argv[i][j];
// 				j++;
// 				continue ;
// 			}
// 			else if (encloser && cmd_argv[i][j] == encloser)
// 			{
// 				encloser = 0;
// 				j++;
// 				continue ;
// 			}
// 			if (encloser != '\'' && cmd_argv[i][j] == '$')
// 			{
// 			}
// 			else
// 				j++;
// 		}
// 		i++;
// 	}
// }
