/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:30:28 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/08 10:43:03 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strdup(char *str)
{
	int		i;
	char	*dup;

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
	char		line[700000];
	static int	buffer_pos;
	static int	buffer_rd;
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
			if (buffer_rd < 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos] == '\n' || buffer[buffer_pos] == '\0')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (strdup(line));
}

int	main(void)
{
	int		fd;
	char	*str;

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
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close (fd);
	printf("\n");
	return (0);
}
