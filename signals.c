/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:57:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/16 14:21:26 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

/*
	In execve, the ignored and defaulted signal handling is inherited.
	Only handled signals are reset (of necessity) to the default handling
	Source: https://stackoverflow.com/questions/2333637/
		is-it-possible-for-a-signal-handler-to-survive-after-exec
		#comment137759046_2333720
*/

void	cmd_sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	cmd_sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_exit_status = 131;
}
