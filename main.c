/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 09:56:12 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*token_list;
	t_cmd	*cmd_table;
	int		err;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	while (1)
	{
		err = 0;
		input = readline("\033[1;32mminishell $ \033[0m");
		if (!input)
			return (ft_putendl_fd("reading error: unable to read input", STDERR_FILENO), 2);
		if (!*input && (free(input), 1))
			continue ;
		add_history(input);
		token_list = lexer(input, &err);
		cmd_table = parser(&token_list, &err);
		free(input);
		token_clear(&token_list);
		if (err > 0)
			continue ;
		if (err < 0)
			break ;
		// executor
		cmd_clear(&cmd_table);
	}
	if (err < 0)
		return (ft_putendl_fd("memory error: unable to assign memory", STDERR_FILENO), 1);
	(void)argv;
	(void)envp;
	return (0);
}
