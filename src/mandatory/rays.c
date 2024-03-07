/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:33:25 by paulo             #+#    #+#             */
/*   Updated: 2024/03/07 00:04:57 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_distances(t_cub3d *cub3d, t_ray_calc *ray_calc);
static void	draw_ray(t_cub3d *cub3d, t_ray_calc *ray_calc);
static void	calc_ray(t_cub3d *cub3d, t_ray_calc *ray_calc);
static void	handler_door(t_cub3d *cub3d, t_ray_calc *ray_calc);

void	distance_rays(t_cub3d *cub3d)
{
	t_ray_calc	ray_calc;

	ray_calc.x = 0;
	while (ray_calc.x < cub3d->mlx_ptr->width)
	{
		ray_calc.camera_x = (2 * ray_calc.x / (double)(cub3d->mlx_ptr->width
					- 1)) - 1;
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
	mlx_texture_t	*texture;

	if (ray_calc->side == 0)
		ray_calc->perp_wall_dist = ray_calc->side_dist.x;
	else
		ray_calc->perp_wall_dist = ray_calc->side_dist.y;
	if (ray_calc->side == 0)
	{
		if (ray_calc->ray.x > 0)
			texture = cub3d->east_texture;
		else
			texture = cub3d->west_texture;
	}
	else
	{
		if (ray_calc->ray.y > 0)
			texture = cub3d->south_texture;
		else
			texture = cub3d->north_texture;
	}
	draw_center_vertical_line(cub3d, ray_calc, texture);
}

static void	calc_ray(t_cub3d *cub3d, t_ray_calc *ray_calc)
{
	calc_distances(cub3d, ray_calc);
	ray_calc->map = (t_vector){(int)cub3d->player.x, (int)cub3d->player.y};
	while (true)
	{
		if (ray_calc->side_dist.x < ray_calc->side_dist.y)
		{
			ray_calc->map.x += ray_calc->step.x;
			ray_calc->side = 0;
		}
		else
		{
			ray_calc->map.y += ray_calc->step.y;
			ray_calc->side = 1;
		}
		if (cub3d->map[(int)ray_calc->map.y][(int)ray_calc->map.x] == '2')
		{
			handler_door(cub3d, ray_calc);
			break ;
		}
		else if (cub3d->map[(int)ray_calc->map.y][(int)ray_calc->map.x] != '0')
			break ;
		if (ray_calc->side_dist.x < ray_calc->side_dist.y)
			ray_calc->side_dist.x += ray_calc->delta_dist.x;
		else
			ray_calc->side_dist.y += ray_calc->delta_dist.y;
	}
	draw_ray(cub3d, ray_calc);
}

static void	handler_door(t_cub3d *cub3d, t_ray_calc *ray_calc)
{
	double wall_x;

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
