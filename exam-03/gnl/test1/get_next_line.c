/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:30:34 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/08 15:13:20 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_double_free(void *a, void *b)
{
	free(a);
	free(b);
	return (NULL);
}

static char	*get_endl(int fd, char *buffer)
{
	char	*temp;
	char	*new_buffer;
	int		rd;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd < 0)
			return (ft_double_free(buffer, temp));
		temp[rd] = 0;
		new_buffer = ft_strjoin(buffer, temp);
		free(buffer);
		buffer = new_buffer;
		if (ft_strchar(buffer, '\n'))
			break ;
	}
	free(temp);
	if (rd == 0 && (!buffer || buffer[0] == '\0'))
		return (ft_double_free(buffer, NULL));
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	if (!line)
		return (ft_double_free(buffer, NULL));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*buffer_update(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_double_free(buffer, NULL));
	new_buffer = ft_calloc((ft_strlen(buffer) - i) + 1, 1);
	if (!new_buffer)
		return (ft_double_free(buffer, NULL));
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_endl(fd, buffer);
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	line = get_line(buffer);
	if (!line || line[0] == '\0')
		return (ft_double_free(buffer, line));
	buffer = buffer_update(buffer);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close (fd);
	return (0);
}
