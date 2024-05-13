/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:29 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/11 07:57:14 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	mini_env(t_info *info, t_cmd *simple_cmd)
{
	t_env	*env;

	(void)simple_cmd;
	env = info->env;
	if (!env)
		return (1);
	while (env)
	{
		if (ft_strchr(env->value, '='))
			ft_putendl_fd(env->value, STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}
