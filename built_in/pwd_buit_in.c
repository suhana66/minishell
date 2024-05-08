/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_buit_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:52 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 13:56:54 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_pwd(t_info *info, t_cmd *simple_cmd)
{
	(void)simple_cmd;
	ft_putendl_fd(info->pwd, 1);
	return (0);
}
