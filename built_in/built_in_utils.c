#include "minishell.h"

char *ft_strndup(const char *src, size_t n)
{
    size_t len;
    char *dst;
    const char *ptr;
    size_t i;

    ptr = src;
    len = 0;
    i = 0;
    while (len < n && *ptr != '\0')
    {
        len++;
        ptr++;
    }
    dst = (char *)malloc(sizeof(char) * (len + 1));
    if (dst == NULL)
        return (NULL);
    ptr = src;
    while (i < len)
    {
        dst[i] = ptr[i];
        i++;
    }
    dst[len] = '\0';
    return (dst);
}

int total_size_env(t_env *l)
{
    int len;

    len = 0;
    while (l && l->next != NULL)
    {
        if (l->value != NULL)
        {
            len += ft_strlen(l->value);
            len++;
        }
        l = l->next;
    }
    return (len);
}

char *env_to_str(t_env *lst)
{
    char *env;
    int i;
    int j;

    env = malloc(sizeof(char) * total_size_env(lst) + 1);
    if (!env)
        return (NULL);
    i = 0;
    while (lst)
    {
        if (lst->value)
        {
            j = 0;
            while (lst->value[j])
            {
                env[i] = lst->value[j];
                i++;
                j++;
            }
        }
        if (lst->next)
            env[i++] = '\n';
        lst = lst->next;
    }
    env[i] = '\0';
    return (env);
}