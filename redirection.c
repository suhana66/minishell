/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:43:26 by susajid           #+#    #+#             */
/*   Updated: 2024/04/18 14:27:09 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_heredoc(char ***cmd_argvp)
{
	char	**argv;
	char	*delimiter;
	size_t	i;

	argv = *cmd_argvp;
	i = 0;
	while (argv[i])
	{
		if (ft_strnstr(argv[i], "<<", ft_strlen(argv[i])))
		{
			delimiter = find_next(argv[i] + 2, argv[i + 1]);
			if (!delimiter)
				return (ft_putstr_fd("parse error\n", 2), 1);
		}
		i++;
	}
	return (0);
}

char	*find_next(char *arg1, char	*arg2)
{
	(void)arg1;
	(void)arg2;
	return (NULL);
}
