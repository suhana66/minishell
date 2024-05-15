/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:37:09 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/13 14:06:45 by smuneer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	check_append_outfile(t_token *redirects)
{
	int	fd;

	if (redirects->type == GREATGREAT)
		fd = open(redirects->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirects->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: infile: No such file or directory\n");
		return (1);
	}
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		printf("minishell: pipe error\n");
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	handle_outfile(t_token *redirects)
{
	int	fd;

	fd = check_append_outfile(redirects);
	if (fd < 0)
	{
		printf("minishell: outfile: Error\n");
		return (1);
	}
	if (fd > 0 && dup2(fd, 1) < 0)
	{
		printf("minishell: pipe error\n");
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	ck_redirects(t_cmd *cmd)
{
	t_token	*start;

	start = cmd->redirects;
	while (cmd->redirects)
	{
		if (cmd->redirects->type == LESS)
		{
			if (handle_infile(cmd->redirects->str))
				return (1);
		}
		else if (cmd->redirects->type == GREAT
			|| cmd->redirects->type == GREATGREAT)
		{
			if (handle_outfile(cmd->redirects))
				return (1);
		}
		else if (cmd->redirects->type == LESSLESS)
		{
			if (handle_infile(cmd->hd_f_name))
				return (1);
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (0);
}

// int main() {

// 	t_info info;
//     info.envv = NULL; // Initialize envv with appropriate values

//     // Create a sample t_cmd structure with redirects
//     t_cmd cmd;
//     cmd.argv = (char *[]){"command", NULL}; // Example argv array
//     cmd.redirects = malloc(sizeof(t_token));
//     if (cmd.redirects == NULL) {
//         perror("Memory allocation failed");
//         return (1);
//     }
// 	cmd.hd_f_name = "input.txt";
//     cmd.redirects->type = LESSLESS; // Example redirect type
//     cmd.redirects->str = NULL; // Example redirect string
//     cmd.redirects->prev = NULL;
//     cmd.redirects->next = NULL;
//     cmd.builtin = NULL; // Example builtin function
//     t_cmd command;
//     // Initialize command with appropriate data, including redirects
//     // For simplicity, assume we have a function to populate a t_cmd structure
// 	int i = 0;
//     // Test Input Redirection
//     i = ck_redirects(&cmd); 
// 	if (i)
// 		printf("error");
// 	else
// 		printf("success");// Should return 0 for successful redirection


//     return 0;
// }