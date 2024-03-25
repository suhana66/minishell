/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:06:28 by susajid           #+#    #+#             */
/*   Updated: 2024/03/25 17:22:01 by susajid          ###   ########.fr       */
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
		return (ft_perror("getcwd"), 1);
	input = prompt;
	prompt = ft_strjoin(input, " % ");
	free(input);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			return (ft_perror("readline"), free(input), free(prompt), 2);
		if (!*input)
			continue ;
		add_history(input);
		cmd_argv = split_cli_input(input, " \t\n", "'\"");
		if (!cmd_argv)
			return (free(input), free(prompt), 3);
		i = 0;
		while (cmd_argv[i])
		{
			if (expand_cmd_arg(&cmd_argv[i++]))
			{
				i = 0;
				while (cmd_argv[i])
					free(cmd_argv[i++]);
				return (free(cmd_argv), free(input), free(prompt), 4);
			}
		}
		i = 0;
		while (cmd_argv[i])
			printf("$%s$\n", cmd_argv[i++]);
		eval(cmd_argv);
		i = 0;
		while (cmd_argv[i])
			free(cmd_argv[i++]);
		free(cmd_argv);
		free(input);
	}
	free(prompt);
	return (0);
}

void	eval(char **cmd_argv)
{
	(void)cmd_argv;
}

void	ft_perror(char *func_name)
{
	ft_putstr_fd(func_name, 2);
	ft_putstr_fd("() error\n", 2);
}
