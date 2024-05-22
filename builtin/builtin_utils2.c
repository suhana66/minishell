#include "minishell.h"

int	check_param(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (export_error(str));
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (0);
}

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **env)
{
	size_t	i;
	size_t	env_len;
	int		ordered;
	char	*t;

	ordered = 0;
	env_len = env_size(env);
	while (env && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				t = env[i];
				env[i] = env[i + 1];
				env[i + 1] = t;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}
