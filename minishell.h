/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/03/25 17:28:49 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readlin

typedef struct s_env
{
	char			**path;
	char			*value;
	char			*key;
	struct s_env	*next;
}				t_env;

typedef struct s_info
{
	int				no_path;
	char			*pwd;
	char			*old_pwd;
	t_env			*envv;
}				t_info;


char	**split_cli_input(char *input, char *delimiters, char *enclosers);
int		expand_cmd_arg(char **cmd_argv);
void	eval(char **cmd_argv);

void	ft_perror(char *func_name);

#endif /* MINISHELL_H */