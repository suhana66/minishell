/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/16 09:10:33 by susajid          ###   ########.fr       */
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
		err = get_cmd_table(&info);
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

int	get_cmd_table(t_info *info)
{
	char	*input;
	t_token	*token_list;
	int		err;

	input = readline("\033[1;32mminishell $ \033[0m");
	if (!input)
	{
		free_info(info);
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(0);
	}
	if (!*input)
		return (free(input), 1);
	add_history(input);
	err = lexer(input, &token_list);
	if (!err)
		err = parser(&token_list, &info->cmd_table);
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
	if (info->pid)
		free (info->pid);
	free(info->pwd);
	free(info->old_pwd);
	cmd_clear(&info->cmd_table);
}

void implement_info(t_info *info)
{
	
}