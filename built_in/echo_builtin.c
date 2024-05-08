#include "../minishell.h"

int n_arg(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return (i);
}

int  echo_b(char **args)
{
    int i;
    int opt;

    i = 1;
    opt = 0;
    if (n_arg(args) > 1)
    {
        while (args[i] && ft_strcmp(args[i], "-n") == 0)
        {
            opt = 1;
            i++;
        }
        while (args[i])
        {
            ft_putstr_fd(args[i], 1);
            if (args[i + 1] && args[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
    }
	if (opt == 0)
	    write(1, "\n", 1);
	return (1);
}