/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:46 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 17:14:04 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_env_var(t_info *info, t_env *to_rem, t_env *p)
{
	if (to_rem)
	{
		if (p)
			p->next = to_rem->next;
		else
			info->envv = to_rem->next;
		if (info->envv && !info->envv->key)
			return (1);
		free(to_rem->key);
		free(to_rem->value);
		free(to_rem);
		return (1);
	}
	return (0);
}

int	check_unset_arg(char *str, t_info *info)
{
	if (ft_strncmp("PATH", str, 4) == 0)
	{
		if (!info->envv)
			return (0);
		printf("check if path must be removed or not");
		return (0);
	}
	return (1);
}

int	del_var(t_env *env, char **str, t_info *info)
{
	t_env	*t;
	t_env	*p;
	t_env	*k;
	int		i;

	i = 1;
	while (str[i])
	{
		t = env;
		while (t)
		{
			if (ft_strncmp(t->key, str[i], ft_strlen(str[i])) == 0)
			{
				k = t;
				break ;
			}
			t = t->next;
		}
		t = env;
		p = NULL;
		check_unset_arg(str[i], info);
		while (t && t != k)
		{
			p = t;
			t = t->next;
		}
		remove_env_var(info, k, p);
		i++;
	}
	return (0);
}

int	error_unset(t_info *info, t_cmd *simple_cmd)
{
	int	i;
	int	j;

	(void)info;
	i = 1;
	if (simple_cmd->argv[1] == NULL)
	{
		printf("error, not valid identifier");
		return (1);
	}
	// print	error as well not enough argument
	while (simple_cmd->argv[i])
	{
		if (!(ft_isalpha(simple_cmd->argv[i][0])) && simple_cmd->argv[i][0] != '_' && simple_cmd->argv[i][0] != '\"' && simple_cmd->argv[i][0] != '\'')
		{
			printf("error, not valid identifier");
			return (1);
		}
		if (equal_s(simple_cmd->argv[i]) != 0)
		{
			printf("error, not valid identifier");
			return (1);
		}
		j = 1;
		while (simple_cmd->argv[i][j])
		{
			if (!ft_isalnum(simple_cmd->argv[i][j]) && simple_cmd->argv[i][j] != '_' && simple_cmd->argv[i][j] != '\'' && simple_cmd->argv[i][j] != '\"')
			{
				printf("error, not valid identifier");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	mini_unset(t_info *info, t_cmd *simple_cmd)
{
	if (error_unset(info, simple_cmd))
		return (1);
	else
		del_var(info->envv, simple_cmd->argv, info);
	return (0);
}