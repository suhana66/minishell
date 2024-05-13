/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:28:02 by susajid           #+#    #+#             */
/*   Updated: 2024/05/11 07:56:39 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int	mini_echo(t_info *info, t_cmd *simple_cmd);

int	mini_pwd(t_info *info, t_cmd *simple_cmd);

int	mini_env(t_info *info, t_cmd *simple_cmd);

int	mini_exit(t_info *info, t_cmd *simple_cmd);
int	determine_exit_code(char **str);
int	is_str_digit(char *str);

#endif /* BUILTIN_H */
