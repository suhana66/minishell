make && make clean && clear && valgrind -s --suppressions=read_line_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell