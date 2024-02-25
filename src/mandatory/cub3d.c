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

void	distance_rays(t_cub3d *cub3d)
{
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	bool		hit;
	t_vector	dir_point;
	t_vector	map_point;
	int			side;
	t_vector	ray;

	map_x = (int)(cub3d->player.x);
	map_y = (int)(cub3d->player.y);
	ray.x = cub3d->dir.x;
	ray.y = cub3d->dir.y;
	if (ray.x == 0)
		delta_dist_x = DBL_MAX;
	else
		delta_dist_x = fabs(1 / ray.x);
	if (ray.y == 0)
		delta_dist_y = DBL_MAX;
	else
		delta_dist_y = fabs(1 / ray.y);
	if (ray.x < 0)
	{
		step_x = -1;
		side_dist_x = (cub3d->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - cub3d->player.x) * delta_dist_x;
	}
	if (ray.y < 0)
	{
		step_y = -1;
		side_dist_y = (cub3d->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - cub3d->player.y) * delta_dist_y;
	}
	hit = false;
	while (hit == false)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (cub3d->map[map_y][map_x] != '0')
			hit = true;
	}
	map_point.x = cub3d->player.x * MINI_MAP_TILE_SIZE;
	map_point.y = cub3d->player.y * MINI_MAP_TILE_SIZE;
	if (side == 0)
	{
		printf("side_dist_x %f\n", side_dist_x);
		dir_point.x = (cub3d->player.x + (cub3d->dir.x * side_dist_x)) * MINI_MAP_TILE_SIZE;
		dir_point.y = (cub3d->player.y + (cub3d->dir.y * side_dist_x)) * MINI_MAP_TILE_SIZE;
		draw_line(cub3d, &map_point, &dir_point, RAY_COLOR / 2);
	}
	else
	{
		printf("side_dist_y %f\n", side_dist_y);
		dir_point.x = (cub3d->player.x + (cub3d->dir.x * side_dist_y)) * MINI_MAP_TILE_SIZE;
		dir_point.y = (cub3d->player.y + (cub3d->dir.y * side_dist_y)) * MINI_MAP_TILE_SIZE;
		draw_line(cub3d, &map_point, &dir_point, RAY_COLOR / 2);
	}
}

void	ft_hook(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	// draw_wallpaper(cub3d, cub3d->floor_color, cub3d->ceiling_color);
	draw_mini_map(cub3d);
	distance_rays(cub3d);
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
