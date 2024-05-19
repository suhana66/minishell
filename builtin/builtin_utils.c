/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:07 by smuneer           #+#    #+#             */
/*   Updated: 2024/05/19 11:42:32 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void path_update (t_info *info)
{
	int i;
	char *temp;

	i = 0;
	temp = NULL;

	array_clear(info->path);
	if(env_search(info->env, "PATH"))
		info->path = ft_split(env_search(info->env, "PATH"), ':');
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