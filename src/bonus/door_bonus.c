/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:35:58 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/03/07 23:57:52 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	toggle_door(t_cub3d *cub3d, int x, int y);

void	handler_door(t_cub3d *cub3d, t_ray_calc *ray_calc)
{
	double	wall_x;

	(void)cub3d;
	if (ray_calc->side == 0)
	{
		wall_x = fabs(ray_calc->ray.x * (ray_calc->side_dist.x
					- ray_calc->side_dist.y));
		if (wall_x > 0.5)
			ray_calc->side_dist.x += ray_calc->delta_dist.x / 2;
		else
			ray_calc->side = 1;
	}
	else
	{
		wall_x = fabs(ray_calc->ray.y * (ray_calc->side_dist.y
					- ray_calc->side_dist.x));
		if (wall_x > 0.5)
			ray_calc->side_dist.y += ray_calc->delta_dist.y / 2;
		else
			ray_calc->side = 0;
	}
}

void	verify_door(t_cub3d *cub3d)
{
	if (cub3d->dir.y < 0 && fabs(cub3d->dir.y) > fabs(cub3d->dir.x))
		toggle_door(cub3d, 0, -1);
	if (cub3d->dir.y > 0 && fabs(cub3d->dir.y) > fabs(cub3d->dir.x))
		toggle_door(cub3d, 0, 1);
	if (cub3d->dir.x < 0 && fabs(cub3d->dir.x) > fabs(cub3d->dir.y))
		toggle_door(cub3d, -1, 0);
	if (cub3d->dir.x > 0 && fabs(cub3d->dir.x) > fabs(cub3d->dir.y))
		toggle_door(cub3d, 1, 0);
}

static void	toggle_door(t_cub3d *cub3d, int x, int y)
{
	int	player_x;
	int	player_y;

	player_x = (int)(cub3d->player.x);
	player_y = (int)(cub3d->player.y);
	if (cub3d->map[player_y + y][player_x + x] == '2')
		cub3d->map[player_y + y][player_x + x] = '3';
	else if (cub3d->map[player_y + y][player_x + x] == '3')
		cub3d->map[player_y + y][player_x + x] = '2';
}
