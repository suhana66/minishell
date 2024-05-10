/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:52 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/09 12:26:08 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(t_info *info, t_cmd *simple_cmd)
{
	(void)simple_cmd;
	ft_putendl_fd(info->pwd, STDOUT_FILENO);
	return (0);
}
