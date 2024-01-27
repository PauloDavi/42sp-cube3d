/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:50:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/27 11:37:50 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		close_finish(int fd);
static size_t	get_size(char *map_file);
static uint32_t	get_mini_map_color(t_cube3d *cube3d, t_point *point);

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
	cube3d->map = malloc((lines_size + 1) * sizeof(char *));
	if (cube3d->map == NULL)
		close_finish(fd);
	cube3d->map[lines_size] = NULL;
	cube3d->map_y = lines_size;
	lines_size = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		cube3d->map[lines_size++] = line;
	}
	close(fd);
}

void	draw_mini_map(t_cube3d *cube3d)
{
	size_t	line_len;
	t_point	point;
	t_point	map_point;
	t_point	initial_point;

	point.y = 0;
	initial_point.x = 100;
	initial_point.y = 100;
	while (point.y < cube3d->map_y)
	{
		point.x = 0;
		line_len = ft_strlen(cube3d->map[(size_t)point.y]);
		while (point.x < line_len)
		{
			if (cube3d->map[(size_t)point.y][(size_t)point.x] != '\n')
			{
				map_point.x = initial_point.x + (point.x * MINI_MAP_TILE_SIZE);
				map_point.y = initial_point.y + (point.y * MINI_MAP_TILE_SIZE);
				draw_square(cube3d, &map_point, MINI_MAP_TILE_SIZE,
					get_mini_map_color(cube3d, &point));
			}
			point.x++;
		}
		point.y++;
	}
}

static uint32_t	get_mini_map_color(t_cube3d *cube3d, t_point *point)
{
	uint32_t	color;
	size_t		x;
	size_t		y;

	x = point->x;
	y = point->y;
	color = 0x00000000;
	if (cube3d->map[y][x] == '1')
		color = 0x000000FF;
	else if (cube3d->map[y][x] == '0')
		color = 0xFFFFFFFF;
	else if (cube3d->map[y][x] == 'N' || cube3d->map[y][x] == 'S'
		|| cube3d->map[y][x] == 'E' || cube3d->map[y][x] == 'W')
		color = 0xFF0000FF;
	return (color);
}

static void	close_finish(int fd)
{
	close(fd);
	exit(EXIT_FAILURE);
}

static size_t	get_size(char *map_file)
{
	char	*line;
	int		fd;
	size_t	lines_size;

	lines_size = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		lines_size++;
		free(line);
	}
	close(fd);
	return (lines_size);
}
