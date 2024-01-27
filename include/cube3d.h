/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:54 by paulo             #+#    #+#             */
/*   Updated: 2024/01/27 11:35:12 by paulo            ###   ########.fr       */
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

# define WIDTH 1024
# define HEIGHT 720
# define MINI_MAP_TILE_SIZE 10

typedef struct s_cube3d
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image;
	char		**map;
	size_t		map_y;

}				t_cube3d;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

void			read_map(t_cube3d *cube3d, char *map_file);
void			draw_mini_map(t_cube3d *cube3d);
void			initialize(t_cube3d *cube3d);
void			draw_square(t_cube3d *cube3d, t_point *point, size_t size,
					int32_t color);
void			free_for_finish(t_cube3d *cube3d);

#endif
