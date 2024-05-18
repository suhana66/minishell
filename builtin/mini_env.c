/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:29 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 14:47:46 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_info *info, t_cmd *simple_cmd)
{
	size_t	i;

	(void)simple_cmd;
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
