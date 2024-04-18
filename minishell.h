/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/04/18 11:49:08 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>

void	eval(char **cmd_argv);

char	**split_cli_input(char *input, char *delimiters, char *enclosers);
size_t	get_token_length(char **input, char *delimiters, char *enclosers);
size_t	get_token_count(char *str, char *delimiters, char *enclosers);
int		expand_cmd_arg(char **cmd_arg);
int		replace_enviornment_variable(char **cmd_arg, size_t *var_i);

void	redirect_heredoc(char ***cmd_argv);

#endif /* MINISHELL_H */