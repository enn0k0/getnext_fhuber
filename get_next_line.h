#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
size_t		ft_strlen(const char *s);
int			has_newline(char *stash);
int			find_newline(char *buffer);
char		*create_line(char *stash, int i);
char		*ft_strjoin(char const *s1, char const *s2);
char		*get_next_line(int fd);

#endif