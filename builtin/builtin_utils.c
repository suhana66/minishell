/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:07 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 14:11:04 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	total_size_env(t_env *env)
{
	int	len;

	len = 0;
	while (env && env->next != NULL)
	{
		if (env->value != NULL)
		{
			len += ft_strlen(env->value);
			len++;
		}
		env = env->next;
	}
	return (len);
}

char	**env_to_str(t_env *lst)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * total_size_env(lst) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->value)
		{
			j = 0;
			while (lst->value[j])
			{
				str[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next)
			str[i++] = '\n';
		lst = lst->next;
	}
	str[i] = '\0';
	return (ft_split(str, '\n'));
}
