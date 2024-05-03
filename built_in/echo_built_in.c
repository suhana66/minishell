#include "../minishell.h"

int n_arg(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return (i);
}

int  echo_b(t_info *info, t_simple_cmd *simple_cmd)
{
    int i;
    int opt;
    int j;

    i = 1;
    opt = 0;
    (void) info;

    if (n_arg(simple_cmd->str) > 1)
    {
        while (simple_cmd->str[i] && ft_strcmp(args[i], "-n") == 0)
        {
            opt = 1;
            i++;
        }
        while (simple_cmd->str[i])
        {
            ft_putstr_fd(args[i], 1);
            if (simple_cmd->str[i + 1] && simple_cmd->str[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
    }
	if (opt == 0)
	    write(1, "\n", 1);
	return (1);
}