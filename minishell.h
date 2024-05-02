/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/02 08:30:08 by susajid          ###   ########.fr       */
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

typedef struct s_env
{
	char			**path;
	char			*value;
	char			*key;
	struct s_env	*next;
}				t_env;

typedef struct s_info
{
	char			*pwd;
	char			*old_pwd;
	t_env			*envv;
}				t_info;

typedef struct s_simple_cmd
{
}	t_simple_cmd;

int		lexer(char *input, t_list **token_list);
t_list	*token_new(char *str, t_type type);
void	token_del(void *token);
int		token_str(char **input, char *delimiters, char **result);
t_type	token_type(char **input);

t_list	*parser(t_list *token_list);
void	parser_token_error(t_type token);

#endif /* MINISHELL_H */
