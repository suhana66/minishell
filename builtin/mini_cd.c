/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:19 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 20:33:06 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_info *info)
{
	char	*t;

	t = ft_strdup(info->pwd);
	free(info->old_pwd);
	info->old_pwd = t;
	free(info->pwd);
	info->pwd = getcwd(NULL, 0);
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
	int		val;
	bool	if_print;

	if_print = false;
	if (!simple_cmd->argv[1])
		val = find_path(info, "HOME=");
	else if (!ft_strncmp(simple_cmd->argv[1], "-", 1) && ft_strlen(simple_cmd->argv[1]) == 1)
	{
		val = find_path(info, "OLDPWD=");
		if_print = true;
	}
	else
	{
		val = chdir(simple_cmd->argv[1]);
		if (val != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->argv[1], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
	}
	if (val != 0)
		return (1);
	change_pwd(info);
	add_pwd_to_env(info);
	if (if_print)
		ft_putendl_fd(info->pwd, STDOUT_FILENO);
	return (0);
}
