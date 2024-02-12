/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:43:10 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/12 15:02:05 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_hook(void *param)
{
	t_cube3d	*cube3d;

	cube3d = param;
	draw_wallpaper(cube3d, cube3d->floor_color, cube3d->ceiling_color);
	// draw_mini_map(cube3d);
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cube3d->mlx_ptr);
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_UP))
		cube3d->player.y -= PLAYER_SPEED;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_DOWN))
		cube3d->player.y += PLAYER_SPEED;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_LEFT))
		cube3d->player.x -= PLAYER_SPEED;
	if (mlx_is_key_down(cube3d->mlx_ptr, MLX_KEY_RIGHT))
		cube3d->player.x += PLAYER_SPEED;
}

int	main(int argc, char **argv)
{
	t_cube3d	cube3d;

	start_params(&cube3d);
	read_map(&cube3d, valid_args(argc, argv));
	valid_map(&cube3d);
	initialize(&cube3d);
	mlx_loop_hook(cube3d.mlx_ptr, ft_hook, &cube3d);
	mlx_loop(cube3d.mlx_ptr);
	free_for_finish(&cube3d);
	mlx_terminate(cube3d.mlx_ptr);
	return (EXIT_SUCCESS);
}

// ENCHER DE ESPAÇOS NA PARTE QUE DEVERIA TER PAREDE
// 1001000000000000000000001->       <---
// 111111111011000001110000000000001