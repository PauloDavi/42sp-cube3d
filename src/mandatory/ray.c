/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:13:12 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/27 21:28:52 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	distance_rays(t_cub3d *cub3d)
{
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	t_vector	dir_point;
	t_vector	map_point;
	int			side;
	t_vector	ray;
	int			x;
	double		cameraX;

	x = 0;
	while (x < WIDTH)
	{
		map_x = (int)(cub3d->player.x);
		map_y = (int)(cub3d->player.y);
		cameraX = (2 * (x / (double)(WIDTH - 1))) - 1;
		ray.x = cub3d->dir.x + cub3d->plane.x * cameraX;
		ray.y = cub3d->dir.y + cub3d->plane.y * cameraX;
		if (ray.x == 0)
			delta_dist_x = DBL_MAX;
		else
			delta_dist_x = fabs(1 / ray.x);
		if (ray.y == 0)
			delta_dist_y = DBL_MAX;
		else
			delta_dist_y = fabs(1 / ray.y);
		if (ray.x < 0)
		{
			step_x = -1;
			side_dist_x = (cub3d->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cub3d->player.x) * delta_dist_x;
		}
		if (ray.y < 0)
		{
			step_y = -1;
			side_dist_y = (cub3d->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cub3d->player.y) * delta_dist_y;
		}
		while (true)
		{
			if (side_dist_x < side_dist_y)
			{
				map_x += step_x;
				side = 0;
			}
			else
			{
				map_y += step_y;
				side = 1;
			}
			if (cub3d->map[map_y][map_x] != '0')
				break ;
			if (side == 0)
				side_dist_x += delta_dist_x;
			else
				side_dist_y += delta_dist_y;
		}
		map_point.x = cub3d->player.x * MINI_MAP_TILE_SIZE;
		map_point.y = cub3d->player.y * MINI_MAP_TILE_SIZE;
		if (side == 0)
		{
			dir_point.x = (cub3d->player.x + (ray.x * side_dist_x))
				* MINI_MAP_TILE_SIZE;
			dir_point.y = (cub3d->player.y + (ray.y * side_dist_x))
				* MINI_MAP_TILE_SIZE;
			// draw_line(cub3d, &map_point, &dir_point, RAY_COLOR / 2);
			draw_center_vertical_line(cub3d, x, (int)(HEIGHT / side_dist_x), 0xFFFFFFFF / 2);
		}
		else
		{
			dir_point.x = (cub3d->player.x + (ray.x * side_dist_y))
				* MINI_MAP_TILE_SIZE;
			dir_point.y = (cub3d->player.y + (ray.y * side_dist_y))
				* MINI_MAP_TILE_SIZE;
			// draw_line(cub3d, &map_point, &dir_point, RAY_COLOR / 2);
			draw_center_vertical_line(cub3d, x, (int)(HEIGHT / side_dist_y), 0xFFFFFFFF);
		}
		x++;
	}
}
