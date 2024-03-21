/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:06:28 by susajid           #+#    #+#             */
/*   Updated: 2024/03/21 10:27:22 by susajid          ###   ########.fr       */
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
		return (perror("getcwd()"), 1);
	input = prompt;
	prompt = ft_strjoin(input, " % ");
	free(input);
	while (1)
	{
		input = readline(prompt);
		// TODO: error condition
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		cmd_argv = split_cli_input(input, " \t\n", "'\"");
		if (!prompt)
			return (perror("split_cli_input()"), 2);
		i = 0;
		while (cmd_argv[i])
		{
			expand_cmd_arg(&cmd_argv[i++]);
			// printf("$%s$\n", cmd_argv[i - 1]);
		}
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
