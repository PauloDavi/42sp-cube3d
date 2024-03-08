/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:10 by paulo             #+#    #+#             */
/*   Updated: 2024/03/07 23:57:52 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	clear_view(t_cub3d *cub3d)
{
	t_vector	point;

	point.y = 0;
	while (point.y < cub3d->mlx_ptr->height)
	{
		point.x = 0;
		while (point.x < cub3d->mlx_ptr->width)
		{
			mlx_put_pixel(cub3d->image, point.x, point.y, 0);
			point.x++;
		}
		point.y++;
	}
}
