/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:26:30 by paulo             #+#    #+#             */
/*   Updated: 2024/03/09 00:20:26 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static uint32_t	get_mini_map_color(t_cub3d *cub3d, t_vector *point);

void	draw_mini_map(t_cub3d *cub3d)
{
	t_vector	point;
	t_vector	map_point;
	double		scale;

	point.y = 0;
	if (cub3d->map_y > cub3d->map_x)
		scale = MINI_MAP_HEIGHT / (cub3d->map_y - 1);
	else
		scale = MINI_MAP_WIDTH / (cub3d->map_x - 1);
	while (point.y < cub3d->map_y)
	{
		point.x = 0;
		while (point.x < cub3d->map_x - 1)
		{
			map_point.x = (point.x * scale);
			map_point.y = (point.y * scale);
			draw_square(cub3d, &map_point, scale, get_mini_map_color(cub3d,
					&point));
			point.x++;
		}
		point.y++;
	}
	draw_player(cub3d, scale);
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
	else if (cub3d->map[y][x] == '3')
		color = OPEN_DOOR_COLOR;
	else if (cub3d->map[y][x] == '2')
		color = CLOSE_DOOR_COLOR;
	return (color);
}
