/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:26:30 by paulo             #+#    #+#             */
/*   Updated: 2024/02/23 01:57:26 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_players(t_cub3d *cub3d);
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
			if (cub3d->map[(size_t)point.y][(size_t)point.x] != '\n' && \
				cub3d->map[(size_t)point.y][(size_t)point.x] != ' ')
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
	draw_players(cub3d);
}

static void	draw_players(t_cub3d *cub3d)
{
	t_vector	map_point;
	t_vector	dir_point;

	dir_point.x = (cub3d->player.x + cub3d->dir.x) * MINI_MAP_TILE_SIZE;
	dir_point.y = (cub3d->player.y + cub3d->dir.y) * MINI_MAP_TILE_SIZE;
	draw_line(cub3d, &map_point, &dir_point, RAY_COLOR);
	draw_circle(cub3d, &map_point, MINI_MAP_TILE_SIZE / 5, PLAYER_COLOR);
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
