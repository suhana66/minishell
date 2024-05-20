/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/20 08:31:52 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	int		err;
	t_info	info;

	if (argc != 1)
		return (ft_putendl_fd("usage: ./minishell", STDERR_FILENO), 1);
	implement_info(&info);
	if (parse_env(&info, envp) || find_pwd(&info))
		return (memory_error(), free_info(&info), 1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		err = get_cmd_table(&info);
		if (err > 0)
			continue ;
		if (err < 0)
			return (memory_error(), free_info(&info), 2);
		signal(SIGINT, cmd_sigint_handler);
		signal(SIGQUIT, cmd_sigquit_handler);
		// executor
		prepare_executor(&info);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		cmd_clear(&info.cmd_table);
	}
	(void)argv;
	free_info(&info);
	return (0);
}

int	get_cmd_table(t_info *info)
{
	char	*input;
	t_token	*token_list;
	int		err;

	input = readline(READLINE_MSG);
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
		err = parser(&token_list, info);
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
	array_clear(info->env);
	free(info->pwd);
	free(info->old_pwd);
	cmd_clear(&info->cmd_table);
	if (info->pip_n)
		free(info->pid);
}

void implement_info(t_info *info)
{
	info->pip_n = 0;
	// g_exit_status = 0;
	// info_pid
}