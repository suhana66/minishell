/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:46 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/22 17:06:27 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ft_strncmp(env[j], argv[i], ft_strlen(argv[i])) == 0
				&& (env[j][ft_strlen(argv[i])] == '='
				|| env[j][ft_strlen(argv[i])] == 0))
				break ;
			j++;
		}
		check_unset_arg(argv[i], info);
		temp = env[j];
		while (env[j++])
			env[j - 1] = env[j];
		free(temp);
		i++;
	}
	return (0);
}

char	*error_unset(t_info *info, t_cmd *simple_cmd)
{
	int	i;
	int	j;

	(void)info;
	i = 1;
	while (simple_cmd->argv[i])
	{
		if (equal_s(simple_cmd->argv[i]) != 0)
			return (simple_cmd->argv[i]);
		j = 1;
		while (simple_cmd->argv[i][j])
		{
			if ((!ft_isalnum(simple_cmd->argv[i][j])
				&& simple_cmd->argv[i][j] != '_'
				&& simple_cmd->argv[i][j] != '\''
				&& simple_cmd->argv[i][j] != '\"')
				|| ft_isdigit(simple_cmd->argv[i][0]))
				return (simple_cmd->argv[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

int	mini_unset(t_info *info, t_cmd *simple_cmd)
{
	char	*not_valid_id;

	not_valid_id = error_unset(info, simple_cmd);
	if (not_valid_id)
	{
		ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
		ft_putstr_fd(not_valid_id, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	del_var(info->env, simple_cmd->argv, info);
	return (0);
}
