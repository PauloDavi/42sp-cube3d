/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:54 by paulo             #+#    #+#             */
/*   Updated: 2024/01/29 21:29:52 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MINI_MAP_TILE_SIZE 30
# define WALL_COLOR 0x000000FF
# define PLAYER_COLOR 0x00FF00FF
# define EMPTY_COLOR 0xFFFFFFFF
# define PLAYER_SPEED 0.03

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_cube3d
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image;
	char		**map;
	size_t		map_y;
	t_vector	player;
}				t_cube3d;

void			read_map(t_cube3d *cube3d, char *map_file);
void			draw_mini_map(t_cube3d *cube3d);
void			initialize(t_cube3d *cube3d);
void			draw_square(t_cube3d *cube3d, t_vector *point, size_t size,
					int32_t color);
void			draw_circle(t_cube3d *cube3d, t_vector *center, int radius,
					int32_t color);
void			free_for_finish(t_cube3d *cube3d);
void			close_finish(int fd);

#endif
