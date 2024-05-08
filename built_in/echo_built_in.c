/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:22 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/08 12:29:23 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int n_arg(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return (i);
}

int  echo_b(t_info *info, t_cmd *simple_cmd)
{
    int i;
    int opt;

    i = 1;
    opt = 0;
    (void) info;

    if (n_arg(simple_cmd->argv) > 1)
    {
        while (simple_cmd->argv[i] && ft_strncmp(simple_cmd->argv[i], "-n", 2) == 0)
        {
            opt = 1;
            i++;
        }
        while (simple_cmd->argv[i])
        {
            ft_putstr_fd(simple_cmd->argv[i], 1);
            if (simple_cmd->argv[i + 1] && simple_cmd->argv[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
    }
	if (opt == 0)
	    write(1, "\n", 1);
	return (1);
}