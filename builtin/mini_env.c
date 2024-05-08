/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:29 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 17:13:22 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_info *info, t_cmd *simple_cmd)
{
	t_env	*t;

	(void)simple_cmd;
	if (!info->envv)
		return (1);
	t = info->envv;
	if (t)
	{
		while (t)
		{
			if (ft_strchr(t->value, '='))
				printf("%s\n", t->value);
			t = t->next;
		}
		return (0);
	}
	else
		return (1);
}
