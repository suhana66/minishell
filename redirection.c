/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:43:26 by susajid           #+#    #+#             */
/*   Updated: 2024/04/19 10:49:13 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_heredoc(void);
void	redirect_input(void);
void	redirect_append(void);
void	redirect_output(void);

int	redirect(char **cmd_argv)
{
	size_t	i;
	size_t	j;
	int		encloser;

	i = 0;
	encloser = 0;
	while (cmd_argv[i])
	{
		j = 0;
		while (cmd_argv[i][j])
		{
			shift_encloser(cmd_argv[i][j], &encloser);
			if (encloser == 0)
			{
				if (cmd_argv[i][j] == '<')
				{
					if (cmd_argv[i][j + 1] == '<')
						redirect_heredoc();
					else
						redirect_input();
				}
				else if (cmd_argv[i][j] == '>')
				{
					if (cmd_argv[i][j + 1] == '>')
						redirect_append();
					else
						redirect_output();
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	redirect_heredoc(void)
{
}

void	redirect_input(void)
{
}

void	redirect_append(void)
{
}

void	redirect_output(void)
{
}
