/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:21 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*token_list;
	int		err;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	while (1)
	{
		err = 0;
		input = readline(READLINE_MSG);
		if (!input)
			return (ft_putendl_fd("reading error: unable to read input", STDERR_FILENO), 2);
		if (!*input && (free(input), 1))
			continue ;
		add_history(input);
		token_list = lexer(input, &err);
		free(input);
		if (err > 0)
			continue ;
		if (err < 0)
			return (3);
		(void)token_list;
		// parser
		// executor
	}
	(void)argv;
	(void)envp;
	return (0);
}
