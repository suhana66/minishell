/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/23 07:01:21 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	(void)argv;
	if (argc != 1)
		return (ft_putendl_fd(USAGE_ERR, STDERR_FILENO), 1);
	info.env = array_dup(envp, array_len(envp) + 1);
	if (!info.env)
		return (1);
	info.exit_status = 0;
	find_pwd(&info);
	implement_info(&info);
	minishell_loop(&info);
	free_info(&info);
	return (0);
}

void	minishell_loop(t_info *info)
{
	int	err;

	err = get_cmd_table(info);
	if (err > 0)
		return ((void)reset_info(info));
	if (err < 0)
	{
		ft_putendl_fd(MEMORY_ERR, STDERR_FILENO);
		free_info(info);
		exit(EXIT_FAILURE);
	}
	prepare_executor(info);
	reset_info(info);
}

int	get_cmd_table(t_info *info)
{
	char	*input;
	t_token	*token_list;
	int		err;

	input = readline(READLINE_MSG);
	if (g_recv_sig == SIGINT)
	{
		info->exit_status = 1;
		g_recv_sig = 0;
	}
	if (!input)
		return (free_info(info), ft_putendl_fd("exit", STDOUT_FILENO),
			exit(EXIT_SUCCESS), 0);
	if (!*input)
		return (free(input), 1);
	add_history(input);
	err = lexer(input, &token_list);
	if (!err && !token_list)
		err = 1;
	if (!err)
		err = parser(&token_list, info);
	free(input);
	token_clear(&token_list);
	return (err);
}

int	event(void)
{
	return (0);
}

void	implement_info(t_info *info)
{
	info->cmd_table = NULL;
	info->reset = false;
	info->pid = NULL;
	info->here_doc = false;
	info->pip_n = 0;
	parse_env(info);
	g_recv_sig = 0;
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
