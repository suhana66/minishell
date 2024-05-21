/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:44:04 by susajid           #+#    #+#             */
/*   Updated: 2024/05/21 11:14:53 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_recv_sig;

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
	{
		free_info(info);
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
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

int	event(void)
{
	return (0);
}

void implement_info(t_info *info)
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
	// info_pid
}

void	reset_info(t_info *info)
{
	cmd_clear(&info->cmd_table);
	if (info->pid)
		free(info->pid);
	array_clear(info->path);
	implement_info(info);
	info->reset = true;
	minishell_loop(info);
}
