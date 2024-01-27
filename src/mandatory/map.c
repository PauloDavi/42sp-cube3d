/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:50:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/27 17:50:44 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static size_t	get_size(char *map_file);
static void		get_player_position(t_cube3d *cube3d, char *line,
					size_t line_size);
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
		get_player_position(cube3d, line, lines_size);
		cube3d->map[lines_size++] = line;
	}
	close(fd);
}

void	draw_mini_map(t_cube3d *cube3d)
{
	size_t	line_len;
	t_point	point;
	t_point	map_point;

	point.y = 0;
	while (point.y < cube3d->map_y)
	{
		point.x = 0;
		line_len = ft_strlen(cube3d->map[(size_t)point.y]);
		while (point.x < line_len)
		{
			if (cube3d->map[(size_t)point.y][(size_t)point.x] != '\n')
			{
				map_point.x = (point.x * MINI_MAP_TILE_SIZE);
				map_point.y = (point.y * MINI_MAP_TILE_SIZE);
				draw_square(cube3d, &map_point, MINI_MAP_TILE_SIZE,
					get_mini_map_color(cube3d, &point));
			}
			point.x++;
		}
		point.y++;
	}
	map_point.x = cube3d->player.x * MINI_MAP_TILE_SIZE;
	map_point.y = cube3d->player.y * MINI_MAP_TILE_SIZE;
	draw_circle(cube3d, &map_point, MINI_MAP_TILE_SIZE / 4, PLAYER_COLOR);
}

static void	get_player_position(t_cube3d *cube3d, char *line, size_t current_y)
{
	char	*ptr;

	ptr = ft_strchr(line, 'N');
	if (ptr == NULL)
	{
		ptr = ft_strchr(line, 'S');
		if (ptr == NULL)
		{
			ptr = ft_strchr(line, 'E');
			if (ptr == NULL)
				ptr = ft_strchr(line, 'W');
		}
	}
	if (ptr != NULL)
	{
		cube3d->player.x = ptr - line;
		cube3d->player.y = current_y;
		*ptr = '0';
	}
}

static uint32_t	get_mini_map_color(t_cube3d *cube3d, t_point *point)
{
	uint32_t	color;
	size_t		x;
	size_t		y;

	x = point->x;
	y = point->y;
	color = 0;
	if (cube3d->map[y][x] == '1' || ft_isspace(cube3d->map[y][x]))
		color = WALL_COLOR;
	else if (cube3d->map[y][x] == '0')
		color = EMPTY_COLOR;
	return (color);
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
