/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:34 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/22 18:57:45 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	if (str[0] != '+' && str[0] != '-' && !ft_isdigit(str[0]))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	determine_exit_code(char **str, t_info *info)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (is_str_digit(str[1]))
		exit_code = (ft_atoi(str[1]) % 256 + 256) % 256;
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit_code = 255;
	}
	free_info(info);
	exit(exit_code);
}

int	mini_exit(t_info *info, t_cmd *simple_cmd)
{
	(void)info;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (simple_cmd->argv[1] && simple_cmd->argv[2])
		return (ft_putendl_fd("minishell: exit: too many arguments",
				STDERR_FILENO), 1);
	determine_exit_code(simple_cmd->argv, info);
	return (0);
}
