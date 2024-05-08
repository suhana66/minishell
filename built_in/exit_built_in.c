#include "../minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	determine_exit_code(char **str)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (is_str_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		printf("numeric argument required\n");
		exit_code = 255;
	}
	//free_arr(str);
	exit(exit_code);
}

int  build_exit(t_info *info, t_simple_cmd *simple_cmd)
{
    printf("exit");
    if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	//str = ft_arrdup(simple_cmd->str);
	// free_tools(tools);
	determine_exit_code(simple_cmd->str);
	return (EXIT_SUCCESS);
}