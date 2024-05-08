/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/08 11:16:04 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_table;
	int		err;
	t_info	info;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	env_st(&info,envp);
	f_pwd(&info);
	while (1)
	{
		err = get_cmd_table(&cmd_table);
		if (err > 0)
			continue ;
		if (err < 0)
			return (1);
		// executor
		cmd_clear(&cmd_table);
	}
	(void)argv;
	(void)envp;
	return (0);
}

int	get_cmd_table(t_cmd **cmd_table)
{
	char	*input;
	t_token	*token_list;
	int		err;

	input = readline("\033[1;32mminishell $ \033[0m");
	if (!input)
		return (ft_putendl_fd("minishell: unable to read input",
				STDERR_FILENO), -1);
	if (!*input)
		return (free(input), 1);
	add_history(input);
	err = lexer(input, &token_list);
	if (!err)
		err = parser(&token_list, cmd_table);
	free(input);
	token_clear(&token_list);
	if (err < 0)
		ft_putendl_fd("minishell: unable to assign memory", STDERR_FILENO);
	return (err);
}
