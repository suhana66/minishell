/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 21:14:17 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*cmd_table;
	int		errcode;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	while (1)
	{
		input = readline(READLINE_MSG);
		if (!input)
			return (ft_putendl_fd("reading error: unable to read input",
					STDERR_FILENO), 2);
		if (!*input && (free(input), 1))
			continue ;
		add_history(input);
		errcode = lexer(input, &cmd_table);
		if (errcode > 0)
			continue ;
		if (errcode < 0)
			return (3);
	}
	(void)argv;
	(void)envp;
	return (0);
}
