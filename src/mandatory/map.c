/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:50:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/26 23:15:10 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	close_finish(int fd)
{
	close(fd);
	exit(EXIT_FAILURE);
}

size_t	get_size(char *map_file)
{
	char	*line;
	int		fd;
	size_t	lines_size;

	lines_size = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while(true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		lines_size++;
		free(line);
	}
	close(fd);
	return (lines_size);
}

void	read_map(t_cube3d *cube3d, char *map_file)
{
	size_t	lines_size;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	lines_size = get_size(map_file);
	if (lines_size == 0)
		close_finish(fd);
	cube3d->map = malloc((lines_size + 1) * sizeof(char*));
	if (cube3d->map == NULL)
		close_finish(fd);
	cube3d->map[lines_size] = NULL;
	cube3d->map_y = lines_size;
	lines_size = 0;
	while(true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		cube3d->map[lines_size++] = line;
	}
	close(fd);
}
