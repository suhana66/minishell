/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 16:32:33 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	input = readline(READLINE_MSG);
	if (!input)
		return (ft_putendl_fd("readline() error", STDERR_FILENO), 2);
	(void)argv;
	(void)envp;
	return (0);
}
