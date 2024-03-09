/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:10 by paulo             #+#    #+#             */
/*   Updated: 2024/03/09 00:14:30 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
