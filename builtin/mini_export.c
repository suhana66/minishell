/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:37 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/23 11:59:47 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exist(char *var, t_info *info)
{
	size_t	i;
	size_t	eq_s;

	if (!info->env)
		return (0);
	i = 0;
	while (info->env[i])
	{
		eq_s = equal_s(info->env[i]);
		if (eq_s == 0)
			eq_s = ft_strlen(info->env[i]);
		if (!(ft_strncmp(info->env[i], var, eq_s)))
		{
			free(info->env[i]);
			info->env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	env_add(char *var, char ***env)
{
	char	**temp;
	size_t	len;

	if (!*env)
		return (0);
	len = array_len(*env);
	temp = array_dup(*env, len + 2);
	if (!temp)
		return (1);
	temp[len] = ft_strdup(var);
	array_clear(*env);
	*env = temp;
	return (0);
}

void	print_with_q(char *str)
{
	char	*pos_e;
	char	*key;

	pos_e = ft_strchr(str, '=');
	key = ft_substr(str, 0, pos_e - str);
	ft_putstr_fd(key, 1);
	ft_putchar_fd('=', 1);
	ft_putchar_fd('"', 1);
	ft_putstr_fd(pos_e + 1, 1);
	ft_putendl_fd("\"", 1);
	free(key);
}

int	dec_sorted(char **env_arr)
{
	int		i;

	if (!env_arr)
		return (0);
	sort_env(env_arr);
	i = 0;
	if (!env_arr)
		return (1);
	while (env_arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(env_arr[i], '='))
			print_with_q(env_arr[i]);
		else
			ft_putendl_fd(env_arr[i], 1);
		i++;
	}
	return (1);
}

int	mini_export(t_info *info, t_cmd *simple_cmd)
{
	int		i;

	if (!info->env)
		return (0);
	if (!simple_cmd->argv[1] || simple_cmd->argv[1][0] == '\0')
		dec_sorted(info->env);
	i = 1;
	while (simple_cmd->argv[i])
	{
		if (check_param(simple_cmd->argv[i]) == 0
			&& !var_exist(simple_cmd->argv[i], info))
			env_add(simple_cmd->argv[i], &info->env);
		if (!ft_strncmp(simple_cmd->argv[i], "PATH=", 5))
			path_update(info);
		free(info->pwd);
		free(info->old_pwd);
		info->pwd = env_search(info->env, "PWD");
		if (info->pwd)
			info->pwd = ft_strdup(info->pwd);
		info->old_pwd = env_search(info->env, "OLDPWD");
		if (info->old_pwd)
			info->old_pwd = ft_strdup(info->old_pwd);
		i++;
	}
	return (0);
}
