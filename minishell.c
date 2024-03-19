/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:06:28 by susajid           #+#    #+#             */
/*   Updated: 2024/03/20 09:21:32 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!input)
			break ;
		add_history(input);
		cmd_argv = parse_cli_input(input);
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
