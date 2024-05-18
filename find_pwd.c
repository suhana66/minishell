/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:30:17 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 16:47:29 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pwd(t_info *info)
{
	size_t	i;

	i = 0;
	while (info->env[i])
	{
		if (!(ft_strncmp(info->env[i], "PWD=", 4)))
		{
			info->pwd = ft_strdup(info->env[i] + 4);
			if (!info->pwd)
				return (1);
		}
		else if (!(ft_strncmp(info->env[i], "OLDPWD=", 7)))
		{
			info->old_pwd = ft_strdup(info->env[i] + 7);
			if (!info->old_pwd)
				return (2);
		}
		i++;
	}
	return (0);
}
