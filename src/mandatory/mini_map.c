/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:26:30 by paulo             #+#    #+#             */
/*   Updated: 2024/02/26 06:21:01 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_mini_map_color(t_cub3d *cub3d, t_vector *point);

void	draw_mini_map(t_cub3d *cub3d)
{
	size_t		line_len;
	t_vector	point;
	t_vector	map_point;

	point.y = 0;
	while (point.y < cub3d->map_y)
	{
		point.x = 0;
		line_len = ft_strlen(cub3d->map[(size_t)point.y]);
		while (point.x < line_len)
		{
			if (cub3d->map[(size_t)point.y][(size_t)point.x] != '\n'
				&& cub3d->map[(size_t)point.y][(size_t)point.x] != ' ')
			{
				map_point.x = (point.x * MINI_MAP_TILE_SIZE);
				map_point.y = (point.y * MINI_MAP_TILE_SIZE);
				draw_square(cub3d, &map_point, MINI_MAP_TILE_SIZE,
					get_mini_map_color(cub3d, &point));
			}
			point.x++;
		}
		point.y++;
	}
}

static uint32_t	get_mini_map_color(t_cub3d *cub3d, t_vector *point)
{
	uint32_t	color;
	size_t		x;
	size_t		y;

	x = point->x;
	y = point->y;
	color = 0;
	if (cub3d->map[y][x] == '1' || ft_isspace(cub3d->map[y][x]))
		color = WALL_COLOR;
	else if (cub3d->map[y][x] == '0')
		color = EMPTY_COLOR;
	return (color);
}
