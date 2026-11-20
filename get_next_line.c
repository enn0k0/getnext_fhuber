#include "get_next_line.h"

char    *read_to_stash(int fd, char *stash, int *endoffile)
{
	ssize_t	 size;
	char	    *buffer;
	char	    *new_stash;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	size = read(fd, buffer, BUFFER_SIZE);
	if (size <= 0)
	{
		free(buffer);
		if (size == 0)
		{
			*endoffile = 1;
			return (stash);
		}
		return (free(stash), NULL);
	}
	buffer[size] = '\0';
	new_stash = ft_strjoin(stash, buffer);
	free(buffer);
	free(stash);
	return (new_stash);
}

static void	save_rest(char *stash, int i, char *rest)
{
	int	 j;
	int	 a;

	a = 0;
	j = i + 1;
	while (stash[j])
	{
		rest[a] = stash[j];
		j++;
		a++;
	}
	rest[a] = '\0';
	free(stash);
}

static char *read_until_newline(int fd, char *stash, int *endoffile)
{
	while (!has_newline(stash) && !*endoffile)
	{
		stash = read_to_stash(fd, stash, endoffile);
		if (!stash)
			return (NULL);
		if ((!*stash && *endoffile == 1))
			return (free(stash), NULL);
	}
	return (stash);
}

char *get_next_line(int fd)
{
	int		 i;
	int		 endoffile;
	char		*str;
	char		*stash;
	static char	rest[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	endoffile = 0;
	stash = ft_strjoin(NULL, rest);
	rest[0] = '\0';
	if (!stash)
		return (NULL);
	stash = read_until_newline(fd, stash, &endoffile);
	if (!stash)
		return (NULL);
	i = find_newline(stash);
	str = create_line(stash, i);
	if (!str)
		return (free(stash), NULL);
	if (stash[i] == '\0')
		return (free(stash), str);
	save_rest(stash, i, rest);
	return (str);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int	 fd;
	char    *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	free(line);
	close(fd);
	return (0);
}
