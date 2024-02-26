/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:43:10 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/19 22:32:22 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	// draw_wallpaper(cub3d, cub3d->floor_color, cub3d->ceiling_color);
	draw_mini_map(cub3d);
	distance_rays(cub3d);
	draw_player(cub3d);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx_ptr);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_W)
		|| mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_UP))
		move_player(cub3d, PLAYER_SPEED);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_S)
		|| mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_DOWN))
		move_player(cub3d, -PLAYER_SPEED);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_A)
		|| mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(cub3d, -PLAYER_ROTATE_SPEED);
	if (mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_D)
		|| mlx_is_key_down(cub3d->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(cub3d, PLAYER_ROTATE_SPEED);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	start_params(&cub3d);
	read_map(&cub3d, valid_args(argc, argv));
	normalize_map(&cub3d);
	valid_map(&cub3d);
	initialize(&cub3d);
	mlx_loop_hook(cub3d.mlx_ptr, ft_hook, &cub3d);
	mlx_loop(cub3d.mlx_ptr);
	free_for_finish(&cub3d);
	mlx_terminate(cub3d.mlx_ptr);
	return (EXIT_SUCCESS);
}
