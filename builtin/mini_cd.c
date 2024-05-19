/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:19 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 14:43:46 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index_var(char *var, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i] && (ft_strncmp(env[i], var, len) || env[i][len] != '='))
		i++;
	if (envp[i])
		return (i);
	return (-1);
}



int	change_pwd(t_info *info, char *old_pd)
{
	char	*t;
	int		flag;

	flag = 0;
	if (get_index_var("PWD", info->env)
		&& ft_strlen(env_search(info->env, "OLDPWD")) != 0
		&& flag == 0)
	{
		old_pd = "";
		flag = 1;
	}
	free(info->old_pwd);
	info->old_pwd = old_pd;
	free(old_pd);
	if (get_index_var("PWD", info->env) != -1)
		return (1);
	free(info->pwd);
	info->pwd = getcwd(NULL, 0);
	return (0);
}

int	find_path(t_info *info, char *str)
{
	char	*tmp;
	int		ret;
	size_t	i;

	ret = -1;
	tmp = NULL;
	i = 0;
	while (info->env[i])
	{
		if ((ft_strncmp(info->env[i], str, ft_strlen(str)) == 0))
		{
			tmp = ft_substr(info->env[i], ft_strlen(str),
					ft_strlen(info->env[i]) - ft_strlen(str));
			break ;
		}
		i++;
	}
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, 2);
		free(str);
		ft_putendl_fd(" not set", 2);
	}
	return (ret);
}

void	add_pwd_to_env(t_info *info)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", info->pwd);
			free(info->env[i]);
			info->env[i] = tmp;
		}
		else if (!ft_strncmp(info->env[i], "OLDPWD=", 7) && info->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", info->old_pwd);
			free(info->env[i]);
			info->env[i] = tmp;
		}
		i++;
	}
}

int	mini_cd(t_info *info, t_cmd *simple_cmd)
{
	int	val;
	char *old_pd;

	old_pd = getcwd(NULL, 0)
	if (!simple_cmd->argv[1] || (ft_strlen(simple_cmd->argv[1] == 1 && simple_cmd->argv[1][0] == '~')))
		val = find_path(info, "HOME=");
	else if (!ft_strncmp(simple_cmd->argv[1], "-", 1) && ft_strlen(simple_cmd->argv[1]) == 1)
		val = find_path(info, "OLDPWD=");
	else
	{
		val = chdir(simple_cmd->argv[1]);
		if (val != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(simple_cmd->argv[1], 2);
			// perror(" ");
		}
	}
	if (val != 0)
		return (1);
	if(change_pwd(info, old_pd));
		return (1);
	add_pwd_to_env(info);
	return (0);
}