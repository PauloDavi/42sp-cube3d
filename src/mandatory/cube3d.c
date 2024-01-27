/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:43:10 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/01/26 23:28:06 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_square(t_cube3d *cube3d, size_t x, size_t y, size_t size, int32_t color)
{
	size_t	current_x;
	size_t	current_y;

	current_y = y;
	while (current_y < (y + size))
	{
		current_x = x;
		while (current_x < (x + size))
		{
			mlx_put_pixel(cube3d->image, current_x, current_y, color);
			current_x++;
		}
		current_y++;
	}	
}

void ft_loop(void* param)
{
	t_cube3d	*cube3d;
	size_t		line_len;
	size_t		x;
	size_t		y;
	size_t		x_init;
	size_t		y_init;
	int32_t		color;

	cube3d = param;
	y = 0;
	x_init = 100;
	y_init = 100;
	while (y < cube3d->map_y)
	{
		x = 0;
		line_len = ft_strlen(cube3d->map[y]);
		while (x < line_len)
		{
			if (cube3d->map[y][x] != '\n') {	
				if (cube3d->map[y][x] == '1')
					color = 0x000000FF;
				else if (cube3d->map[y][x] == '0')
					color = 0xFFFFFFFF;
				else
					color = 0xFF0000FF;
				draw_square(cube3d, x_init + (x * MINI_MAP_TILE_SIZE), y_init + (y * MINI_MAP_TILE_SIZE), MINI_MAP_TILE_SIZE, color);
			}
			x++;
		}
		y++;
	}
}

void ft_hook(void* param)
{
	t_cube3d *cube3d;

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

void free_for_finish(t_cube3d* cube3d)
{
	ft_free_split(cube3d->map);
	mlx_delete_image(cube3d->mlx_ptr, cube3d->image);
}

int32_t main(void)
{
	t_cube3d cube3d;

	read_map(&cube3d, "maps/map1.cub");
	initialize(&cube3d);
	
	mlx_loop_hook(cube3d.mlx_ptr, ft_loop, &cube3d);

	mlx_loop(cube3d.mlx_ptr);
	free_for_finish(&cube3d);
	mlx_terminate(cube3d.mlx_ptr);
	return (EXIT_SUCCESS);
}
