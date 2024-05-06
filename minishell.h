/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/06 14:44:32 by susajid          ###   ########.fr       */
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
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

int		get_cmd_table(t_cmd **cmd_table);

int		lexer(char *input, t_token **token_list);
int		token_str(char **input, char *delimiters, char **result);
t_type	token_type(char **input);

t_token	*token_add(t_type type, char *str, t_token **tokens);
void	token_delone(t_token **token);
void	token_clear(t_token **tokens);
void	array_clear(char **array);

t_cmd	*parser(t_token **token_list, int *err);
t_token	*cmd_redirects(t_token **token_list, int *err);
char	**cmd_argv(t_token **token_list);
void	type_error(t_token *token);

t_cmd	*cmd_new(char **argv, t_token *redirects);
void	cmd_addback(t_cmd **cmds, t_cmd *node);
void	cmd_delone(t_cmd **cmd);
void	cmd_clear(t_cmd **cmds);

#endif /* MINISHELL_H */
