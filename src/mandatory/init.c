/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:24:46 by paulo             #+#    #+#             */
/*   Updated: 2024/01/27 11:25:21 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initialize(t_cube3d *cube3d)
{
	cube3d->mlx_ptr = mlx_init(WIDTH, HEIGHT, "MLX42", false);
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
