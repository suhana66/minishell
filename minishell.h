/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/01 13:59:56 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

# define READLINE_MSG	"\033[1;32mminishell$ \033[0m"

typedef enum e_token_type
{
	PIPE,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS
}	t_token_type;

typedef struct s_token
{
	t_token_type	token_type;
	char			*str;
}	t_token;

typedef struct s_simple_cmd
{
}	t_simple_cmd;

int		ft_perror(int errnum);

t_list	*lexer(char *input);
void	token_del(void *token);
size_t	token_length(char **input, char *delimiters);

t_list	*parser(t_list *token_list);
void	parser_token_error(t_token_type token);

#endif /* MINISHELL_H */
