/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 12:09:28 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

# define READLINE_MSG	"\033[1;32mminishell$ \033[0m"

typedef enum e_token
{
	PIPE,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS
}	t_token;

typedef struct s_lexer
{
	t_token			token_type;
	char			*str;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_simple_cmd
{
}	t_simple_cmd;

int				ft_perror(int errnum);

t_lexer			*lexer(char *input);
t_lexer			*lexer_new(t_token token_type, char *str);
void			lexer_clear(t_lexer **token_list);
size_t			lexer_token_length(char **input, char *delimiters);

t_simple_cmd	*parser(t_lexer *token_list);
void 			parser_token_error(t_token token);

#endif /* MINISHELL_H */
