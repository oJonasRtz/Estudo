/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:54:25 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/07 13:32:03 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strdup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	while (str[i])
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_rd;
	static int	buffer_pos;
	char		line[70000];
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	while (1)
	{
		if (buffer_pos >= buffer_rd)
		{
			buffer_rd = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_rd <= 0)
				break ;
			
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (strdup(line));
}

int	main(void)
{
	char	*str;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close (fd);
	return (0);
}
