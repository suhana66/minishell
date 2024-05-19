/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:52 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/19 13:40:45 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(t_info *info, t_cmd *simple_cmd)
{
	char	*result;
	(void)simple_cmd;
	(void)info;
	result = getcwd(NULL, 0);
	ft_putendl_fd(result, STDOUT_FILENO);
	free(result);
	return (0);
}
