/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuneer <smuneer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:11 by susajid           #+#    #+#             */
/*   Updated: 2024/05/23 17:57:19 by smuneer          ###   ########.fr       */
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

extern int	g_recv_sig;

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

// main
int		get_cmd_table(t_info *info);
void	implement_info(t_info *info);
void	minishell_loop(t_info *info);
int		event(void);

// cmd_utils
void	process_exit(t_info *info, int exit_code);
void	reset_info(t_info *info);
int		get_exit_status(int cmd_status);
void	dup_cmd(t_cmd *cmd, t_info *info, int end[2], int fd_in);
int		prepare_executor(t_info *info);

// lexer
int		lexer(char *input, t_token **token_list);
int		token_str(char **input, char *delimiters, char **result);
t_type	token_type(char **input);
char	get_encloser(char c, char *encloser);
void	type_error(t_token *token);

// token_utils
t_token	*token_add(t_type type, char *str, t_token **tokens);
void	token_delone(t_token **token);
void	token_clear(t_token **tokens);
size_t	count_pipes(t_token *token_list);

// parser
int		parser(t_token **token_list, t_info *info);
int		cmd_redirects(t_token **token_list, t_token **result);
char	**cmd_argv(t_token **token_list);
int		(*cmd_builtin(char *argv_0))(t_info *info, t_cmd *cmd);
int		ft_strcasecmp(const char *s1, const char *s2);

// arr_utils
size_t	array_len(char **array);
char	**array_dup(char **array, size_t size);
void	array_clear(char **array);

// parse_env
int		parse_env(t_info *info);
char	**split_path_in_env(char **env);
int		find_pwd(t_info *info);
char	*env_search(char **env, char *key);

// builtin
int		mini_echo(t_info *info, t_cmd *simple_cmd);
int		mini_cd(t_info *info, t_cmd *simple_cmd);
int		mini_pwd(t_info *info, t_cmd *simple_cmd);
int		mini_export(t_info *info, t_cmd *simple_cmd);
int		mini_unset(t_info *info, t_cmd *simple_cmd);
int		mini_env(t_info *info, t_cmd *simple_cmd);
int		mini_exit(t_info *info, t_cmd *simple_cmd);

// expander
int		expander(t_cmd *cmd, t_info *info);
int		parse_arg(char **str, t_info *info, bool if_del_quotes, bool if_expand);
int		replace_enviornment_variable(char **str, size_t *var_i, char **env);
int		replace_exit_status(char **str, size_t *var_i, int exit_status);
int		replace_str(char **str, size_t *start, size_t len, char *rep_val);

// signals
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	cmd_sigint_handler(int sig);
void	heredoc_sigint_handler(int sig);

// single_cmd
int		find_cmd(t_cmd *cmd, t_info *info);
void	handle_cmd(t_cmd *cmd, t_info *info);
void	single_cmd(t_cmd *cmd, t_info *info);
t_cmd	*cmd_add(t_cmd **cmds);
void	cmd_clear(t_cmd **cmds);

// redirection
int		check_append_outfile(t_token *redirects);
int		handle_infile(char *file);
int		handle_outfile(t_token *redirects);
int		ck_redirects(t_cmd *cmd);

// heredoc
int		here_doc(t_token *heredoc, bool quotes, t_info *info, char *f_name);
int		send_heredoc(t_info *info, t_cmd *cmd);
char	*heredoc_temp_file(void);
int		ft_heredoc(t_info *info, t_token *heredoc, char *f_name);

// execution
int		pipe_wait(int *pid, int pipe_n);
int		ft_fork(t_info *info, int end[2], int fd_in, t_cmd *cmd);
int		check_fd_heredoc(t_info *info, int end[2], t_cmd *cmd);
int		many_cmd_executor(t_info *info);
t_cmd	*ft_simple_cmdsfirst(t_cmd *cmd);

// buitin/mini_cd
void	change_pwd(t_info *info);
int		find_path(t_info *info, char *str);
void	add_pwd_to_env(t_info *info, char *str);

// buitin/mini_exit
void	determine_exit_code(char **str, t_info *info);
int		is_str_digit(char *str);

// buitin/mini_export
int		var_exist(char *var, t_info *info);
int		env_add(char *var, char ***env);
void	print_with_q(char *str);
int		dec_sorted(char **env_arr);

// builtin/builtin_utils
int		equal_s(char *str);
void	path_update(t_info *info);
int		export_error(char *c);
int		check_valid_identifier(char c);

// builtin/builtin_utils2
int		check_param(char *str);
int		env_size(char **env);
void	sort_env(char **env);

// buitin/mini_unset
void	check_unset_arg(char *str, t_info *info);
int		del_var(char **env, char **argv, t_info *info);
char	*error_unset(t_info *info, t_cmd *simple_cmd);

#endif /* MINISHELL_H */
