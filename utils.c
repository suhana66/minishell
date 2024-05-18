/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:25:20 by susajid           #+#    #+#             */
/*   Updated: 2024/05/18 13:59:04 by susajid          ###   ########.fr       */
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

int	prepare_executor(t_info *info)
{
	//signal(SIGQUIT, sigquit_handler);
	//g_global.in_cmd = 1;
	if (info->pipes == 0)
		single_cmd(info->cmds, info);
	else
	{
		info->pid = ft_calloc(sizeof(int), info->pip_n + 2);
		if (!info->pid)
		{
			ft_putstr_fd("memory error: unable to assign memory\n", 2);
			reset_info(info);
			return(1);
		}
		many_cmd_executor(info);
	}
	return (0);
}