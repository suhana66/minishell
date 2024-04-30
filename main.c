/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 17:18:42 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lexer	*tokens;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	while (1)
	{
		input = readline(READLINE_MSG);
		if (!input)
			return (ft_putendl_fd("readline() error", STDERR_FILENO), 2);
		if (!*input && (free(input), 1))
			continue ;
		add_history(input);
		tokens = lexer(input);
	}
	(void)tokens;
	(void)argv;
	(void)envp;
	return (0);
}

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
t_lexer	*lexer(char *input)
{
	char	*delimiters;
	char	*enclosers;

	delimiters = " \t\n";
	enclosers = "\"\'";
	(void)delimiters;
	(void)enclosers;
	(void)input;
	return (NULL);
}
