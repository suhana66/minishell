/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:30:17 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/10 23:06:40 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pwd(t_info *info)
{
	t_env	*env;

	env = info->env;
	info->old_pwd = NULL;
	info->pwd = NULL;
	while (env)
	{
		if (!(ft_strncmp(env->value, "PWD=", 4)))
		{
			if (info->pwd == NULL)
				info->pwd = ft_strdup(env->value + 4);
		}
		else if (!(ft_strncmp(env->value, "OLDPWD=", 7)))
		{
			if (info->old_pwd == NULL)
				info->old_pwd = ft_strdup(env->value + 7);
		}
		env = env->next;
	}
	if (!info->pwd || !info->old_pwd)
		return (0);
	return (1);
}
