/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:06:28 by susajid           #+#    #+#             */
/*   Updated: 2024/04/18 13:13:38 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Bash delimiters can be found in the variable IFS (Internal Field Separator)
int	main(void)
{
	char	*prompt;
	char	*input;
	char	**cmd_argv;
	size_t	i;

	prompt = getcwd(NULL, 0);
	if (!prompt)
		return (ft_putstr_fd("getcwd() error", 2), 1);
	input = prompt;
	prompt = ft_strjoin(input, " % ");
	free(input);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			return (ft_putstr_fd("readline() error", 2), free_all(prompt, input, NULL), 2);
		if (!*input)
			continue ;
		add_history(input);
		cmd_argv = split_cli_input(input, " \t\n", "'\"");
		if (!cmd_argv)
			return (free_all(prompt, input, cmd_argv), 3);
		if (redirect_heredoc(&cmd_argv))
			return (free_all(prompt, input, cmd_argv), 4);
		i = 0;
		while (cmd_argv[i])
			if (expand_cmd_arg(&cmd_argv[i++]))
				return (free_all(prompt, input, cmd_argv), 5);
		eval(cmd_argv);
		free_all(NULL, input, cmd_argv);
	}
	free(prompt);
	return (0);
}

void	eval(char **cmd_argv)
{
	(void)cmd_argv;
}

void	free_all(char *prompt, char *input, char **cmd_argv)
{
	size_t	i;

	if (prompt)
		free(prompt);
	if (input)
		free(input);
	if (cmd_argv)
	{
		i = 0;
		while (cmd_argv[i])
			free(cmd_argv[i++]);
		free(cmd_argv);
	}
}
