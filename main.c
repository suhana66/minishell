/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajidstudent.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/13 11:14:11 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		err;
	t_info	info;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	if (parse_env(&info, envp) || find_pwd(&info))
		return (memory_error(), free_info(&info), 1);
	while (1)
	{
		err = get_cmd_table(&info.cmd_table);
		if (err > 0)
			continue ;
		if (err < 0)
			return (memory_error(), free_info(&info), 2);
		// executor
		cmd_clear(&info.cmd_table);
	}
	(void)argv;
	info.env_arr = envp;
	free_info(&info);
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
	return (err);
}

void	memory_error(void)
{
	ft_putendl_fd("minishell: unable to assign memory", STDERR_FILENO);
}

void	free_info(t_info *info)
{
	array_clear(info->path);
	free_env(info->env);
	free(info->pwd);
	free(info->old_pwd);
	cmd_clear(&info->cmd_table);
}
