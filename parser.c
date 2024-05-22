/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:39:23 by susajid           #+#    #+#             */
/*   Updated: 2024/05/22 22:26:45 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token **token_list, t_info *info)
{
	int		err;
	t_cmd	*node;

	info->cmd_table = NULL;
	info->pip_n = count_pipes(*token_list);
	if ((*token_list)->type == PIPE)
		return (type_error(*token_list), 1);
	while (*token_list)
	{
		if (*token_list && (*token_list)->type == PIPE)
			token_delone(token_list);
		if (!*token_list || (*token_list)->type == PIPE)
			return (cmd_clear(&info->cmd_table), type_error(*token_list), 1);
		node = cmd_add(&info->cmd_table);
		if (!node)
			return (cmd_clear(&info->cmd_table), -1);
		err = cmd_redirects(token_list, &node->redirects);
		if (err)
			return (cmd_clear(&info->cmd_table), err);
		node->argv = cmd_argv(token_list);
		if (!node->argv)
			return (cmd_clear(&info->cmd_table), -1);
		node->builtin = cmd_builtin(node->argv[0]);
	}
	return (0);
}

int	cmd_redirects(t_token **token_list, t_token **result)
{
	t_token	*node;
	t_token	*token;
	char	*str;

	token = *token_list;
	*result = NULL;
	while (1)
	{
		while (token && !token->type)
			token = token->next;
		if (!token || token->type == PIPE)
			break ;
		if (!token->next || token->next->type)
			return (token_clear(result), type_error(token->next), 1);
		str = ft_strdup(token->next->str);
		node = token_add(token->type, str, result);
		if (!str || !node)
			return (token_clear(result), -1);
		if (token == *token_list)
			*token_list = token->next->next;
		token_delone(&token);
		token_delone(&token);
	}
	return (0);
}

char	**cmd_argv(t_token **token_list)
{
	t_token	*temp;
	size_t	argc;
	char	**result;
	size_t	i;

	temp = *token_list;
	argc = 0;
	while (temp && temp->type != PIPE && ++argc)
		temp = temp->next;
	result = (char **)malloc((argc + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[argc] = NULL;
	i = 0;
	while (i < argc)
	{
		result[i] = ft_strdup((*token_list)->str);
		if (!result[i++])
			return (array_clear(result), NULL);
		token_delone(token_list);
	}
	return (result);
}

/*
	returns a function pointer with the prototype:
		int	func(t_info *, t_cmd *);
	case-sensitive builtin functions:
		export, unset, exit
*/
int	*cmd_builtin(char *argv_0)
{
	static void	*builtins[][2] = {
	{"echo", mini_echo},
	{"cd", mini_cd},
	{"pwd", mini_pwd},
	{"export", mini_export},
	{"unset", mini_unset},
	{"env", mini_env},
	{"exit", mini_exit},
	{NULL}
	};
	int			i;

	i = 0;
	while (argv_0 && builtins[i][0])
	{
		if (((builtins[i][1] == mini_echo || builtins[i][1] == mini_cd
			|| builtins[i][1] == mini_pwd || builtins[i][1] == mini_env)
			&& !ft_strcasecmp(argv_0, builtins[i][0]))
			|| (ft_strlen(builtins[i][0]) == ft_strlen(argv_0)
			&& !ft_strncmp(builtins[i][0], argv_0, ft_strlen(argv_0))))
			return (builtins[i][1]);
		i++;
	}
	return (NULL);
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	if (s1[i] == 0 && s2[i] == 0)
		return (0);
	return (1);
}
