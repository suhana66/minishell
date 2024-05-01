/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 10:29:32 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lexer	*tokens;

	if (argc != 1)
		return (ft_perror(1));
	while (1)
	{
		input = readline(READLINE_MSG);
		if (!input)
			return (ft_perror(2));
		if (!*input && (free(input), 1))
			continue ;
		add_history(input);
		tokens = lexer(input);
		if (!tokens)
			return (-1);
		lexer_clear(tokens);
	}
	(void)argv;
	(void)envp;
	return (0);
}

int	ft_perror(int errnum)
{
	char	*errmsg;

	if (errnum == 1)
		errmsg = "usage: ./minishell";
	else if (errnum == 2)
		errmsg = "reading error: unable to read input";
	else if (errnum == 3)
		errmsg = "memory error: unable to assign memory";
	else if (errnum == 10)
		errmsg = "syntax error: unable to locate closing quote";
	else
		errmsg = "error";
	if (errnum)
		ft_putendl_fd(errmsg, STDERR_FILENO);
	return (errnum);
}
