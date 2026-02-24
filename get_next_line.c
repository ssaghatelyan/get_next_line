/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:55:02 by ssaghate          #+#    #+#             */
/*   Updated: 2026/02/24 19:43:14 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	read_and_join(int fd, char **rest, char *buffer)
{
	int		bytes;
	char	*tmp;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
		return (bytes);
	buffer[bytes] = '\0';
	tmp = ft_strjoin(*rest, buffer);
	if (!tmp)
		return (-1);
	*rest = tmp;
	return (1);
}

static char	*free_all(char *buffer, char **rest)
{
	free(buffer);
	free(*rest);
	*rest = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*line;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	status = 1;
	while ((rest == NULL || !ft_strchr(rest, '\n')) && status > 0)
	{
		status = read_and_join(fd, &rest, buffer);
		if (status == -1)
			return (free_all(buffer, &rest));
	}
	if (!rest || rest[0] == '\0')
		return (free_all(buffer, &rest));
	line = take_line(rest);
	if (!line)
		return (free_all(buffer, &rest));
	rest = clean_rest(rest);
	free(buffer);
	return (line);
}
