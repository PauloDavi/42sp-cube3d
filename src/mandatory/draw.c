/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:10 by paulo             #+#    #+#             */
/*   Updated: 2024/01/27 17:48:09 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_cube3d *cube3d, t_point *point, size_t size,
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

void	draw_circle(t_cube3d *cube3d, t_point *center, int radius,
		int32_t color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_put_pixel(cube3d->image, center->x + x, center->y + y,
					color);
			x++;
		}
		y++;
	}
}
