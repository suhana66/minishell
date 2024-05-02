#include "minishell.h"

t_env *copy_env(char *str)
{
    t_env t;
    int key_l;
    char *pos_equal;

    t = malloc(sizeof(t_env))
    if (!t)
        return (NULL);
    pos_equal = ft_strchr(str, '=');
    if (!pos_equal || pos_equal==str)
        return (free(t), NULL);
    //check if key_l should be size_t
    key_l = pos_equal - str;
    t->key = malloc(key_l + 1);
    if (!t->key)
        return(free(t), NULL);
    ft_strncpy(t->key, str, key_l);
    t->key[key_l] = '\0';
    //check if value should be after =
    t->value = ft_strdup(str);
    t->next = NULL;
    return (t);
}

void free_env(t_env *head)
{
    t_env t;

    while (head)
    {
        t = head;
        head = head->next;
        free(t->key);
        free(t->value);
        free(temp);
    }
}


t_env  *add_env(char **env)
{
    int i;
    t_env *f;
    t_env *t;
    t_env *n;

    i = 0;
    f = NULL;
    t = NULL;
    n = NULL;
    while (env[i])
    {
        n = copy_env(env[i]);
        if (!n)
        {
            free_env(f);
            return (0);
        }
        if (!f)
            f = n;
        else
            t->next = n;
        t = n;
        i++;
    }
    return (f);
}

char *find_path_in_env(char **env)
{
    char  *e_path;
    int i;

    e_path = NULL;
    i = 0;
    while (env[i])
    {
        if(!(ft_strncmp(env[i], "PATH=", 5)))
        {
            e_path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
            break;
        }
        i++;
    }
    if (!e_path)
        return (NULL);
    return (e_path);
}

int env_st(t_info *info, char **env)
{
    int i;
    char *t;

    info->envv = add_env(env);
    t = find_path_in_env(env);
    info->envv->path = ft_split(t, ':');
    i = 0;
    free(t);
    if (!info->envv || !info->envv->path)
    {
        free_env(info->envv);
        //error "env"
        exit(0)
    }
    while (info->envv->path[i])
    {
        if (info->envv->path[i][ft_strlen(info->envv->path[i]) - 1] != '/')
        {
            t = ft_strjoin(info->envv->path[i], "/");
            free(info->envv->path[i]);
            info->envv->path[i] = t;
        }
        i++;
    }
    return (0);
}