/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:22 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/10 07:23:52 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(t_info *info, t_cmd *simple_cmd)
{
	int	i;
	int	opt;
	int	j;

	i = 1;
	opt = 0;
	(void)info;
	while (simple_cmd->argv[i] && ft_strncmp(simple_cmd->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (simple_cmd->argv[i][j] == 'n')
			j++;
		if (simple_cmd->argv[i][j])
			break ;
		opt = 1;
		i++;
	}
	while (simple_cmd->argv[i])
		if (ft_putstr_fd(simple_cmd->argv[i++], STDOUT_FILENO),
			simple_cmd->argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	if (!opt)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
