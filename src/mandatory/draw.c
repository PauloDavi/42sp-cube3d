/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:10 by paulo             #+#    #+#             */
/*   Updated: 2024/02/01 20:39:15 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_cube3d *cube3d, t_vector *point, size_t size,
		int32_t color)
{
	size_t	current_x;
	size_t	current_y;

	current_y = point->y;
	while (current_y < (point->y + size))
	{
		current_x = point->x;
		while (current_x < (point->x + size))
		{
			mlx_put_pixel(cube3d->image, current_x, current_y, color);
			current_x++;
		}
		current_y++;
	}
}

void	draw_circle(t_cube3d *cube3d, t_vector *center, int radius,
		int32_t color)
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
				mlx_put_pixel(cube3d->image, center->x + x, center->y + y, \
						color);
			x++;
		}
		y++;
	}
}

void	draw_wallpaper(t_cube3d *cube3d, int32_t floor_color,
		int32_t ceiling_color)
{
	t_vector	vector;
	uint32_t	color;

	vector.y = 0;
	color = ceiling_color;
	while (vector.y < cube3d->mlx_ptr->height)
	{
		vector.x = 0;
		if (vector.y > cube3d->mlx_ptr->height / 2)
			color = floor_color;
		while (vector.x < cube3d->mlx_ptr->width)
		{
			mlx_put_pixel(cube3d->image, vector.x, vector.y, color);
			vector.x++;
		}
		vector.y++;
	}
}
