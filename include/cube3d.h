#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define WIDTH 512
# define HEIGHT 512
# define MINI_MAP_TILE_SIZE 10

typedef struct s_cube3d
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image;
	char		**map;
	size_t		map_y;

}				t_cube3d;

void	read_map(t_cube3d *cube3d, char *map_file);

#endif
