/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:07 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/18 14:11:04 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	total_size_env(t_env *env)
{
	int	len;

	len = 0;
	while (env && env->next != NULL)
	{
		if (env->value != NULL)
		{
			len += ft_strlen(env->value);
			len++;
		}
		env = env->next;
	}
	return (len);
}

char	**env_to_str(t_env *lst)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * total_size_env(lst) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->value)
		{
			j = 0;
			while (lst->value[j])
			{
				str[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next)
			str[i++] = '\n';
		lst = lst->next;
	}
	str[i] = '\0';
	return (ft_split(str, '\n'));
}

void path_update (t_info *info)
{
	t_env *e;
	int i;
	char *temp;

	i = 0;
	e = info->env;
	temp = NULL;

	free_array(info->path);
	while (e)
	{
		if (!(ft_strncmp(e->key, "PATH", 4)))
		{
			info->path = ft_split(e->value, ':');
			break;
		}
		e = e->next;
	}
	while (info->path[i])
	{
		if (info->path[i][ft_strlen(info->path[i]) - 1] != '/')
		{
			temp = ft_strjoin(info->path[i], "/");
			free(info->path[i]);
			info->path[i] = temp;
		}
		i++;
	}
}

// #include <stdio.h> // Include necessary headers
// #include <stdlib.h> // Include necessary headers
// #include <string.h> // Include necessary headers

// // Define your t_info and t_env structures and path_update function here

// int main() {
//     // Initialize necessary variables or data structures
//     t_info info;
//     // Assuming you have initialized the 'info' structure and its members appropriately
//     info.path = NULL; // Initialize path to NULL
//     info.env = NULL; // Initialize env to NULL

//     // Create an example t_env structure representing the PATH environment variable
//     t_env *path_env = malloc(sizeof(t_env));
//     path_env->key = strdup("PATH");
//     path_env->value = strdup("/usr/local/bin:/usr/bin:/bin");
//     path_env->next = NULL;

//     // Link the path_env node to the info structure
//     info.env = path_env;

//     // Call the path_update function to update the path member
//     path_update(&info);

//     // Print the updated path member for testing
//     printf("Updated PATH: ");
//     if (info.path != NULL) {
//         for (int i = 0; info.path[i] != NULL; i++) {
//             printf("%s ", info.path[i]);
//         }
//     } else {
//         printf("NULL");
//     }
//     printf("\n");

//     // Free allocated memory
//     free(path_env->key);
//     free(path_env->value);
//     free(path_env);
//     // Free any memory allocated in path_update function, if necessary

//     return 0;
// }