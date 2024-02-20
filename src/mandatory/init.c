/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:24:46 by paulo             #+#    #+#             */
/*   Updated: 2024/02/19 22:32:24 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initialize(t_cube3d *cube3d)
{
	cube3d->mlx_ptr = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (cube3d->mlx_ptr == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cube3d->image = mlx_new_image(cube3d->mlx_ptr, WIDTH, HEIGHT);
	if (cube3d->image == NULL)
	{
		mlx_close_window(cube3d->mlx_ptr);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cube3d->mlx_ptr, cube3d->image, 0, 0) == -1)
	{
		mlx_close_window(cube3d->mlx_ptr);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
}

void	start_params(t_cube3d *cube3d)
{
	cube3d->pos.x = 5;
	cube3d->pos.y = 5;
	cube3d->dir.x = -1;
	cube3d->dir.y = 0;
	cube3d->plane.x = 0;
	cube3d->plane.y = 0.66;
	cube3d->west_texture = NULL;
	cube3d->north_texture = NULL;
	cube3d->east_texture = NULL;
	cube3d->south_texture = NULL;
	cube3d->floor_color = -1;
	cube3d->ceiling_color = -1;
}
