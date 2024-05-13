/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajidstudent.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:30:17 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/13 11:11:53 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pwd(t_info *info)
{
	t_env	*env;

	env = info->env;
	while (env)
	{
		if (!(ft_strncmp(env->value, "PWD=", 4)))
		{
			info->pwd = ft_strdup(env->value + 4);
			if (!info->pwd)
				return (1);
		}
		else if (!(ft_strncmp(env->value, "OLDPWD=", 7)))
		{
			info->old_pwd = ft_strdup(env->value + 7);
			if (!info->old_pwd)
				return (2);
		}
		env = env->next;
	}
	return (0);
}
