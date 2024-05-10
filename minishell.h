/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/10 18:14:27 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>

typedef struct s_info
{
	char			**path;
	char			*pwd;
	char			*old_pwd;
	struct s_env	*env;
}	t_info;

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
}	t_env;

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
	struct s_token	*redirects;
	int				(*builtin)(struct s_info *, struct s_cmd *);
	struct s_cmd	*next;
}	t_cmd;

int		get_cmd_table(t_cmd **cmd_table);
void	memory_error(void);

int		lexer(char *input, t_token **token_list);
int		token_str(char **input, char *delimiters, char **result);
t_type	token_type(char **input);

t_token	*token_add(t_type type, char *str, t_token **tokens);
void	token_delone(t_token **token);
void	token_clear(t_token **tokens);

int		parser(t_token **token_list, t_cmd **cmd_table);
int		cmd_redirects(t_token **token_list, t_token **result);
char	**cmd_argv(t_token **token_list);
int		(*cmd_builtin(char *argv_0))(t_info *, t_cmd *cmd);
void	type_error(t_token *token);

t_cmd	*cmd_add(t_cmd **cmds);
void	cmd_clear(t_cmd **cmds);
void	array_clear(char **array);

int		parse_env(t_info *info, char **env);
char	**split_path_in_env(char **env);
t_env	*env_new(char *str);
t_env	*env_list(char **env);
void	free_env(t_env *head);

int		f_pwd(t_info *info);
char	*env_to_str(t_env *lst);
char	*ft_strndup(const char *src, size_t n);
int		equal_s(char *str);
int		check_valid_identifier(char c);

#endif /* MINISHELL_H */
