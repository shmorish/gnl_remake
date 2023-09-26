/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 23:58:23 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/27 00:51:30 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, char **store)
{
	int		read_size;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
			return (free(buf), NULL);
		buf[read_size] = '\0';
		if (store[fd] == NULL)
			store[fd] = ft_strdup(buf);
		else
			store[fd] = ft_strjoin(store[fd], buf);
		if (store[fd] == NULL)
			return (free(buf), NULL);
		if (ft_strchr(store[fd], '\n') || read_size == 0)
			break ;
	}
	return (free(buf), store[fd]);
}

char	*concat_to_line(char *store)
{
	char	*line;
	size_t	i;

	i = 0;
	while (store[i] != '\n' && store[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (store[i] != '\n' && store[i] != '\0')
	{
		line[i] = store[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*update_store(char *store)
{
	char	*new_store;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (store[i] != '\n' && store[i] != '\0')
		i++;
	if (store[i] == '\0')
	{
		free(store);
		return (NULL);
	}
	new_store = (char *)malloc(sizeof(char) * (ft_strlen(store) - i + 1));
	if (!new_store)
		return (NULL);
	i++;
	while (store[i] != '\0')
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	free(store);
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*line;

	if (fd < 0 || OPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = read_buffer(fd, store);
	if (store[fd] == NULL)
		return (NULL);
	line = concat_to_line(store[fd]);
	if (line == NULL)
		return (NULL);
	store[fd] = update_store(store[fd]);
	if (store[fd] == NULL)
		return (NULL);
	return (line);
}

// #include <libc.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	fd = open("gnl.c", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("line:[%d]    [%s]", i++, line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 	}
// 	close(fd);
// 	return (system("leaks -q gnl"));
// }
