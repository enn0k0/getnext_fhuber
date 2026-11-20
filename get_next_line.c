#include "get_next_line_0.h"

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

static char *save_rest(char *stash, int i)
{
	char    *new_stash;
	int	 j;
	int	 a;

	a = 0;
	j = i + 1;
	new_stash = malloc(ft_strlen(stash) - i);
	if (!new_stash)
		return (free(stash), NULL);
	while (stash[j])
	{
		new_stash[a] = stash[j];
		j++;
		a++;
	}
	new_stash[a] = '\0';
	free(stash);
	return (new_stash);
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
	static char *stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	endoffile = 0;
	stash = read_until_newline(fd, stash, &endoffile);
	if (!stash)
		return (NULL);
	i = find_newline(stash);
	str = create_line(stash, i);
	if (!str)
		return (free(stash), stash = NULL, NULL);
	if (stash[i] == '\0')
		return (free(stash), stash = NULL, str);
	stash = save_rest(stash, i);
	if (!stash)
		return (free(str), NULL);
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
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
