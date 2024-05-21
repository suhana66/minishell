/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/21 13:55:26 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

# define READLINE_MSG	"\033[1;32mminishell $ \033[0m"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"

# define USAGE_ERR	"usage: ./minishell"
# define MEMORY_ERR	"minishell: unable to assign memory"

typedef struct s_info
{
	char			**path;
	char			*pwd;
	char			*old_pwd;
	char			**env;
	struct s_cmd	*cmd_table;
	int				*pid;
	int				pip_n;
	bool			here_doc;
	bool			reset;
	int				exit_status;
}	t_info;

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
	char			*hd_f_name;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

int		get_cmd_table(t_info *info);
void	implement_info(t_info *info);
void	free_info(t_info *info);
void	minishell_loop(t_info *info);
void	reset_info(t_info *info);

char	get_encloser(char c, char *encloser);
size_t	count_pipes(t_token *token_list);
size_t	array_len(char **array);
char	**array_dup(char **array, size_t size);

int		lexer(char *input, t_token **token_list);
int		token_str(char **input, char *delimiters, char **result);
t_type	token_type(char **input);

t_token	*token_add(t_type type, char *str, t_token **tokens);
void	token_delone(t_token **token);
void	token_clear(t_token **tokens);

int		parser(t_token **token_list, t_info *info);
int		cmd_redirects(t_token **token_list, t_token **result);
char	**cmd_argv(t_token **token_list);
int		(*cmd_builtin(char *argv_0))(t_info *, t_cmd *cmd);
void	type_error(t_token *token);

t_cmd	*cmd_add(t_cmd **cmds);
void	cmd_clear(t_cmd **cmds);
void	array_clear(char **array);

int		parse_env(t_info *info);
char	**split_path_in_env(char **env);
int		find_pwd(t_info *info);

int		mini_echo(t_info *info, t_cmd *simple_cmd);
int		mini_cd(t_info *info, t_cmd *simple_cmd);
int		mini_pwd(t_info *info, t_cmd *simple_cmd);
int		mini_export(t_info *info, t_cmd *simple_cmd);
int		mini_unset(t_info *info, t_cmd *simple_cmd);
int		mini_env(t_info *info, t_cmd *simple_cmd);
int		mini_exit(t_info *info, t_cmd *simple_cmd);

int		expander(t_cmd *cmd, t_info *info);
int		parse_arg(char **str, t_info *info, bool if_del_quotes, bool if_expand);
int		replace_enviornment_variable(char **str, size_t *var_i, char **env);
int		replace_exit_status(char **str, size_t *var_i, int exit_status);
char	*env_search(char **env, char *key);

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	cmd_sigint_handler(int sig);
void	heredoc_sigint_handler(int sig);

int		determine_exit_code(char **str, t_info *info);
int		send_heredoc(t_info *info, t_cmd *cmd);
int		ck_redirects(t_cmd *cmd);
void	handle_cmd(t_cmd *cmd, t_info *info);
int		equal_s(char *str);
int		is_str_digit(char *str);

int		ck_redirects(t_cmd *cmd);
char	*del_quotes(char *str, char c);

int		prepare_executor(t_info *info);
int		many_cmd_executor(t_info *info);
void	single_cmd(t_cmd *cmd, t_info *info);
int		get_exit_status(int cmd_status);
void	path_update(t_info *info);

int		export_error(char *c);

#endif /* MINISHELL_H */
