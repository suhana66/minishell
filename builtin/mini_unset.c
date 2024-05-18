/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:46 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 19:06:16 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	remove_env_var(t_info *info, t_env *to_rem, t_env *p)
// {
// 	if (to_rem)
// 	{
// 		if (p)
// 			p->next = to_rem->next;
// 		else
// 			info->env = to_rem->next;
// 		if (info->env && !info->env->key)
// 			return (1);
// 		free(to_rem->key);
// 		free(to_rem->value);
// 		free(to_rem);
// 		return (1);
// 	}
// 	return (0);
// }

void	check_unset_arg(char *str, t_info *info)
{
	if (!str)
		return ;
	if (ft_strncmp("PATH", str, 4) == 0)
	{
		array_clear(info->path);
		info->path = NULL;
	}
	if (ft_strncmp("PWD", str, 3) == 0)
	{
		free(info->pwd);
		info->pwd = NULL;
	}
	if (ft_strncmp("OLDPWD", str, 6) == 0)
	{
		free(info->old_pwd);
		info->old_pwd = NULL;
	}
}

int	del_var(char **env, char **argv, t_info *info)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (env[j])
		{
			if (ft_strncmp(env[j], argv[i], ft_strlen(argv[i])) == 0 && (env[j][ft_strlen(argv[i])] == '=' || env[j][ft_strlen(argv[i])] == 0))
				break ;
			j++;
		}
		check_unset_arg(argv[i], info);
		temp = env[j];
		while (env[j])
		{
			env[j] = env[j + 1];
			j++;
		}
		free(temp);
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
		del_var(info->env, simple_cmd->argv, info);
	return (0);
}
