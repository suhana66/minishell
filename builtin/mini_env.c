/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:29 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/23 11:38:34 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_info *info, t_cmd *simple_cmd)
{
	size_t	i;

	if (simple_cmd->argv[1])
		return (ft_putendl_fd("minishell: env: too many arguments",
				STDERR_FILENO), 1);
	if (!info->env)
		return (1);
	i = 0;
	while (info->env[i])
	{
		if (ft_strchr(info->env[i], '='))
			ft_putendl_fd(info->env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
