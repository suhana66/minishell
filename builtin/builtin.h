/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:28:02 by susajid           #+#    #+#             */
/*   Updated: 2024/05/10 23:30:59 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int	mini_echo(t_info *info, t_cmd *simple_cmd);
int	mini_pwd(t_info *info, t_cmd *simple_cmd);
int	mini_env(t_info *info, t_cmd *simple_cmd);

#endif /* BUILTIN_H */
