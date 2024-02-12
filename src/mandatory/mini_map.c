/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:26:30 by paulo             #+#    #+#             */
/*   Updated: 2024/02/12 12:27:28 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static uint32_t	get_mini_map_color(t_cube3d *cube3d, t_vector *point);

void	draw_mini_map(t_cube3d *cube3d)
{
	size_t		line_len;
	t_vector	point;
	t_vector	map_point;

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

static uint32_t	get_mini_map_color(t_cube3d *cube3d, t_vector *point)
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
