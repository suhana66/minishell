/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/04 21:22:23 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

# define READLINE_MSG	"\033[1;32mminishell $ \033[0m"
# define MEM_ERR_MSG	"memory error: unable to assign memory"

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
	t_token			*redirects;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

t_token	*lexer(char *input, int *err);
char	*token_str(char **input, char *delimiters, int *err);
t_type	token_type(char **input);

t_token	*token_new(char *str, t_type type);
void	token_addback(t_token **tokens, t_token *node);
size_t	token_count(t_token *tokens);
void	token_delone(t_token **token);
void	token_clear(t_token **tokens);

t_cmd	*parser(t_token **token_list, int *err);
t_token	*cmd_redirects(t_token **token_list, int *err);
void	type_error(t_type token);

t_cmd	*cmd_new(t_token **token_list, int *err);
void	cmd_addback(t_cmd **cmds, t_cmd *node);
void	cmd_delone(t_cmd **cmd);
void	cmd_clear(t_cmd **cmds);

#endif /* MINISHELL_H */
