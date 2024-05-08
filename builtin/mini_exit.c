/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:34 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 17:13:54 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	determine_exit_code(char **str)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (is_str_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		printf("numeric argument required\n");
		exit_code = 255;
	}
	//free_arr(str);
	exit(exit_code);
}

int	mini_exit(t_info *info, t_cmd *simple_cmd)
{
	(void)info;
	printf("exit");
	if (simple_cmd->argv[1] && simple_cmd->argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	//str = ft_arrdup(simple_cmd->argv);
	// free_tools(tools);
	determine_exit_code(simple_cmd->argv);
	return (EXIT_SUCCESS);
}
