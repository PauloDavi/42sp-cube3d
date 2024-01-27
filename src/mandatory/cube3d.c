/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:43:10 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/27 11:34:02 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_loop(void *param)
{
	draw_mini_map(param);
}

void	ft_hook(void *param)
{
	t_cube3d	*cube3d;

	cube3d = param;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cube3d->mlx_ptr);
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_UP))
		cube3d->image->instances[0].y -= 5;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_DOWN))
		cube3d->image->instances[0].y += 5;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_LEFT))
		cube3d->image->instances[0].x -= 5;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_RIGHT))
		cube3d->image->instances[0].x += 5;
}

int32_t	main(void)
{
	t_cube3d	cube3d;

	read_map(&cube3d, "maps/map1.cub");
	initialize(&cube3d);
	mlx_loop_hook(cube3d.mlx_ptr, ft_loop, &cube3d);
	mlx_loop_hook(cube3d.mlx_ptr, ft_hook, &cube3d);
	mlx_loop(cube3d.mlx_ptr);
	free_for_finish(&cube3d);
	mlx_terminate(cube3d.mlx_ptr);
	return (EXIT_SUCCESS);
}
