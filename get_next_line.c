#include "get_next_line.h"

static char	*take_line(char *rest)
{
	int		i;

	if (!rest || !rest[0])
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	return (ft_substr(rest, 0, i));
}

static char	*clean_rest(char *rest)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	new = malloc(ft_strlen(rest) - i + 1);
	if (!new)
	{
		free(rest);
		return (NULL);
	}
	j = 0;
	while (rest[i])
		new[j++] = rest[i++];
	new[j] = '\0';
	free(rest);
	return (new);
}

char	*get_next_line(int fd)
{
	int				bytes;
	static char		*rest;
	char			*line;
	char			buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(rest, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		rest = ft_strjoin(rest, buffer);
	}
	if (!rest)
		return (NULL);
	line = take_line(rest);
	rest = clean_rest(rest);
	return (line);
}
