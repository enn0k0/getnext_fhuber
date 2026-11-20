#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

int has_newline(char *stash)
{
    int i;

    i = 0;
    if (!stash)
        return (0);
    while (stash[i])
    {
        if (stash[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

int find_newline(char *buffer)
{
    int i;

    i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
        i++;
    return (i);
}

char    *create_line(char *stash, int i)
{
    char    *str;
    int     j;

    j = 0;
    str = malloc(i + 1 + (stash[i] == '\n'));
    if (!str)
        return (NULL);
    while (j < i + (stash[i] == '\n'))
    {
        str[j] = stash[j];
        j++;
    }
    str[j] = '\0';
    return (str);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  i;
    size_t  j;
    char    *res_malloc;

    if (!s1)
        s1 = "";
    res_malloc = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!res_malloc)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        res_malloc[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        res_malloc[i] = s2[j];
        i++;
        j++;
    }
    res_malloc[i] = '\0';
    return (res_malloc);
}