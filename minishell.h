/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 16:15:06 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

typedef enum e_type
{
	PIPE = 1,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	t_token			*redirects;
	struct s_cmd	*next;
}	t_cmd;

int		get_cmd_table(t_cmd **cmd_table);

int		lexer(char *input, t_token **token_list);
int		token_str(char **input, char *delimiters, char **result);
t_type	token_type(char **input);

t_token	*token_add(t_type type, char *str, t_token **tokens);
void	token_delone(t_token **token);
void	token_clear(t_token **tokens);

int		parser(t_token **token_list, t_cmd **cmd_table);
int		cmd_redirects(t_token **token_list, t_token **result);
char	**cmd_argv(t_token **token_list);
void	type_error(t_token *token);

t_cmd	*cmd_add(char **argv, t_token *redirects, t_cmd **cmds);
void	cmd_clear(t_cmd **cmds);
void	array_clear(char **array);

#endif /* MINISHELL_H */
