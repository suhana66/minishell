/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:19 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 17:13:41 by susajid          ###   ########.fr       */
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
	t_env	*t;

	ret = -1;
	tmp = NULL;
	t = info->envv;
	while (t)
	{
		if ((ft_strncmp(t->value, str, ft_strlen(str)) == 0))
		{
			tmp = ft_substr(t->value, ft_strlen(str),
					ft_strlen(t->value) - ft_strlen(str));
			break ;
		}
		t = t->next;
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
	t_env	*t;
	char	*tmp;

	t = info->envv;
	while (t)
	{
		if (!ft_strncmp(t->value, "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", info->pwd);
			free(t->value);
			t->value = tmp;
		}
		else if (!ft_strncmp(t->value, "OLDPWD=", 7) && info->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", info->old_pwd);
			free(t->value);
			t->value = tmp;
		}
		t = t->next;
	}
}

int	mini_cd(t_info *info, t_cmd *simple_cmd)
{
	int	val;

	if (!simple_cmd->argv[1])
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
	change_pwd(info);
	add_pwd_to_env(info);
	return (0);
}