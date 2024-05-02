/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 12:57:34 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

# define READLINE_MSG	"\033[1;32mminishell$ \033[0m"
# define MEM_ERR_MSG	"memory error: unable to assign memory"

typedef enum e_type
{
	PIPE,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*str;
}	t_token;

typedef struct s_cmd
{
	t_list	*redirects;
}	t_cmd;

t_list	*lexer(char *input, int *err);
t_list	*token_new(char *str, t_type type);
void	token_del(void *token);
char	*token_str(char **input, char *delimiters, int *err);
t_type	token_type(char **input);

t_list	*parser(t_list **token_list, int *err);
t_cmd	*cmd_new(t_list **token_list, int *err);
void	cmd_del(void *simple_cmd);
void	type_error(t_type token);

#endif /* MINISHELL_H */
