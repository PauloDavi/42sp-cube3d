/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:10 by paulo             #+#    #+#             */
/*   Updated: 2024/02/27 21:04:22 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub3d *cub3d, t_vector *point, size_t size, int32_t color)
{
	size_t	current_x;
	size_t	current_y;

	current_y = point->y;
	while (current_y < (point->y + size))
	{
		current_x = point->x;
		while (current_x < (point->x + size))
		{
			if (current_y == point->y || current_y == (point->y + size - 1)
				|| current_x == point->x || current_x == (point->x + size - 1))
				mlx_put_pixel(cub3d->image, current_x, current_y, color / 2);
			else
				mlx_put_pixel(cub3d->image, current_x, current_y, color);
			current_x++;
		}
		current_y++;
	}
}

void	draw_players(t_cub3d *cub3d)
{
	t_vector	map_point;
	t_vector	dir_point;
	t_vector	plane_point;

	map_point.x = cub3d->player.x * MINI_MAP_TILE_SIZE;
	map_point.y = cub3d->player.y * MINI_MAP_TILE_SIZE;
	dir_point.x = (cub3d->player.x + cub3d->dir.x) * MINI_MAP_TILE_SIZE;
	dir_point.y = (cub3d->player.y + cub3d->dir.y) * MINI_MAP_TILE_SIZE;
	plane_point.x = (cub3d->player.x + cub3d->dir.x + cub3d->plane.x) * MINI_MAP_TILE_SIZE;
	plane_point.y = (cub3d->player.y + cub3d->dir.y + cub3d->plane.y) * MINI_MAP_TILE_SIZE;
	draw_line(cub3d, &dir_point, &plane_point, RAY_COLOR);
	plane_point.x = (cub3d->player.x + cub3d->dir.x - cub3d->plane.x) * MINI_MAP_TILE_SIZE;
	plane_point.y = (cub3d->player.y + cub3d->dir.y - cub3d->plane.y) * MINI_MAP_TILE_SIZE;
	draw_line(cub3d, &dir_point, &plane_point, RAY_COLOR);
	draw_line(cub3d, &map_point, &dir_point, RAY_COLOR);
	draw_circle(cub3d, &map_point, MINI_MAP_TILE_SIZE / 5, PLAYER_COLOR);
}

void	draw_circle(t_cub3d *cub3d, t_vector *center, int radius, int32_t color)
{
	int	x;
	int	y;
	int	hypo;

	y = -radius;
	hypo = radius * radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= hypo)
				mlx_put_pixel(cub3d->image, center->x + x, center->y + y,
					color);
			x++;
		}
		y++;
	}
}

void	draw_wallpaper(t_cub3d *cub3d, int32_t floor_color,
		int32_t ceiling_color)
{
	t_vector	vector;
	uint32_t	color;

	vector.y = 0;
	color = ceiling_color;
	while (vector.y < cub3d->mlx_ptr->height)
	{
		vector.x = 0;
		if (vector.y > cub3d->mlx_ptr->height / 2)
			color = floor_color;
		while (vector.x < cub3d->mlx_ptr->width)
		{
			mlx_put_pixel(cub3d->image, vector.x, vector.y, color);
			vector.x++;
		}
		vector.y++;
	}
}

void	draw_center_vertical_line(t_cub3d *cub3d, int x, int length, int color)
{
	int	y;
	int	max_y;

	max_y = (cub3d->mlx_ptr->height + length) / 2;
	if (max_y > cub3d->mlx_ptr->height)
		max_y = cub3d->mlx_ptr->height;
	y = (cub3d->mlx_ptr->height - length) / 2;
	if (y < 0)
		y = 0;
	while (y < max_y)
	{
		mlx_put_pixel(cub3d->image, x, y, color);
		y++;
	}
}

void	draw_line(t_cub3d *cub3d, t_vector *point1, t_vector *point2, int color)
{
	int		steps;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;

	if (abs((int)(point2->x - point1->x)) > abs((int)(point2->y - point1->y)))
		steps = abs((int)(point2->x - point1->x));
	else
		steps = abs((int)(point2->y - point1->y));
	x_increment = (point2->x - point1->x) / steps;
	y_increment = (point2->y - point1->y) / steps;
	x = point1->x;
	y = point1->y;
	while (steps--)
	{
		mlx_put_pixel(cub3d->image, (int)x, (int)y, color);
		x += x_increment;
		y += y_increment;
	}
}
