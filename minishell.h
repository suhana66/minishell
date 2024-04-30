/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 17:09:33 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

# define READLINE_MSG	"\033[1;32mminishell$ \033[0m"

enum e_token
{
	WORD,
	PIPE,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS
};

typedef struct s_lexer
{
	enum e_token	token_type;
	char			*str;
	struct s_lexer	*next;
}	t_lexer;

t_lexer	*lexer(char *input);

#endif /* MINISHELL_H */
