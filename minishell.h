/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/04/19 10:15:39 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>

void	eval(char **cmd_argv);
void	free_all(char *prompt, char *input, char **cmd_argv);
int		shift_encloser(char cmd_arg_c, int *encloser);

char	**split_cli_input(char *input, char *delimiters);
size_t	get_token_length(char **input, char *delimiters);
size_t	get_token_count(char *input, char *delimiters);
int		expand_cmd_arg(char **cmd_arg);
int		replace_enviornment_variable(char **cmd_arg, size_t *var_i);

int		redirect(char **cmd_argv);

#endif /* MINISHELL_H */