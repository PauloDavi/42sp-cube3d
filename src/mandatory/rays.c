/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:33:25 by paulo             #+#    #+#             */
/*   Updated: 2024/02/26 09:47:31 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_distances(t_cub3d *cub3d, t_ray_calc *ray_calc);
static void	draw_ray(t_cub3d *cub3d, t_ray_calc *ray_calc);
static void	calc_ray(t_cub3d *cub3d, t_ray_calc *ray_calc);

void	distance_rays(t_cub3d *cub3d)
{
	t_ray_calc	ray_calc;

	ray_calc.x = 0;
	while (ray_calc.x < WIDTH)
	{
		ray_calc.camera_x = (2 * ray_calc.x / (double)(WIDTH - 1)) - 1;
		ray_calc.ray.x = cub3d->dir.x + (cub3d->plane.x * ray_calc.camera_x);
		ray_calc.ray.y = cub3d->dir.y + (cub3d->plane.y * ray_calc.camera_x);
		calc_ray(cub3d, &ray_calc);
		ray_calc.x++;
	}
}

static void	calc_distances(t_cub3d *cub3d, t_ray_calc *ray_calc)
{
	ray_calc->delta_dist.x = safe_ray_dist_calc(ray_calc->ray.x);
	ray_calc->delta_dist.y = safe_ray_dist_calc(ray_calc->ray.y);
	ray_calc->step.x = get_signal(ray_calc->ray.x);
	ray_calc->step.y = get_signal(ray_calc->ray.y);
	if (ray_calc->ray.x < 0)
		ray_calc->side_dist.x = (cub3d->player.x - (int)cub3d->player.x)
			* ray_calc->delta_dist.x;
	else
		ray_calc->side_dist.x = ((int)cub3d->player.x + 1.0 - cub3d->player.x)
			* ray_calc->delta_dist.x;
	if (ray_calc->ray.y < 0)
		ray_calc->side_dist.y = (cub3d->player.y - (int)cub3d->player.y)
			* ray_calc->delta_dist.y;
	else
		ray_calc->side_dist.y = ((int)cub3d->player.y + 1.0 - cub3d->player.y)
			* ray_calc->delta_dist.y;
}

static void	draw_ray(t_cub3d *cub3d, t_ray_calc *ray_calc)
{
	double	perp_wall_dist;
	int		color;

	ray_calc->side_dist.x -= ray_calc->delta_dist.x;
	ray_calc->side_dist.y -= ray_calc->delta_dist.y;
	ray_calc->map_point.x = cub3d->player.x * MINI_MAP_TILE_SIZE;
	ray_calc->map_point.y = cub3d->player.y * MINI_MAP_TILE_SIZE;
	if (ray_calc->side == 0)
	{
		ray_calc->dir_point.x = (cub3d->player.x + (ray_calc->ray.x
					* ray_calc->side_dist.x)) * MINI_MAP_TILE_SIZE;
		ray_calc->dir_point.y = (cub3d->player.y + (ray_calc->ray.y
					* ray_calc->side_dist.x)) * MINI_MAP_TILE_SIZE;
		perp_wall_dist = ray_calc->side_dist.x;
		color = WALL_COLOR;
	}
	else
	{
		ray_calc->dir_point.x = (cub3d->player.x + (ray_calc->ray.x
					* ray_calc->side_dist.y)) * MINI_MAP_TILE_SIZE;
		ray_calc->dir_point.y = (cub3d->player.y + (ray_calc->ray.y
					* ray_calc->side_dist.y)) * MINI_MAP_TILE_SIZE;
		perp_wall_dist = ray_calc->side_dist.y;
		color = WALL_COLOR / 2;
	}
	// draw_line(cub3d, &ray_calc->map_point, &ray_calc->dir_point, RAY_COLOR);
	draw_center_vertical_line(cub3d, ray_calc->x, cub3d->mlx_ptr->height
		/ perp_wall_dist, color);
}

static void	calc_ray(t_cub3d *cub3d, t_ray_calc *ray_calc)
{
	calc_distances(cub3d, ray_calc);
	ray_calc->map = (t_vector){(int)cub3d->player.x, (int)cub3d->player.y};
	while (true)
	{
		if (ray_calc->side_dist.x < ray_calc->side_dist.y)
		{
			ray_calc->side_dist.x += ray_calc->delta_dist.x;
			ray_calc->map.x += ray_calc->step.x;
			ray_calc->side = 0;
		}
		else
		{
			ray_calc->side_dist.y += ray_calc->delta_dist.y;
			ray_calc->map.y += ray_calc->step.y;
			ray_calc->side = 1;
		}
		if (cub3d->map[(int)ray_calc->map.y][(int)ray_calc->map.x] != '0')
			break ;
	}
	draw_ray(cub3d, ray_calc);
}
