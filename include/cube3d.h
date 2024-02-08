/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:54 by paulo             #+#    #+#             */
/*   Updated: 2024/02/08 20:23:19 by bedos-sa         ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 800
# define MINI_MAP_TILE_SIZE 30
# define PLAYER_COLOR 0x00FF00FF
# define WALL_COLOR 0x000000FF
# define EMPTY_COLOR 0xFFFFFFFF
# define FLOOR_COLOR 0xA85032FF
# define CEILING_COLOR 0x3248A8FF
# define PLAYER_SPEED 0.03
# define VALID_CHAR_SET "01NSEW\n "
# define VALID_CHAR_SET_PLAYER "NSEW"
# define FILE_EXTENSION ".cub"
# define ERR_INVALID_CHAR "Error\nInvalid map char '%d'\n"
# define ERR_INVALID_PLAYER "Error\nInvalid number of players '%d'\n"
# define WEST "WE"
# define NORTH "NO"
# define EAST "EA"
# define SOUTH "SO"
# define FLOOR "F"
# define CEILING "C"


typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_cube3d
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*image;
	char			**map;
	size_t			map_y;
	t_vector		player;
	mlx_texture_t*	west_texture;
	mlx_texture_t*	north_texture;
	mlx_texture_t*	east_texture;
	mlx_texture_t*	south_texture;
	int64_t			floor_color;
	int64_t			ceiling_color;
}				t_cube3d;

// finish
void			free_for_finish(t_cube3d *cube3d);
void			close_finish(int fd);
void			err_exit(char *str);
void			close_err_exit(int fd, char *str);

// map
void			read_map(t_cube3d *cube3d, char *map_file);
void			draw_mini_map(t_cube3d *cube3d);
void			get_player_position(t_cube3d *cube3d, char *line, size_t current_y);

// draw
void			draw_square(t_cube3d *cube3d, t_vector *point, size_t size,
					int32_t color);
void			draw_circle(t_cube3d *cube3d, t_vector *center, int radius,
					int32_t color);
void 			draw_wallpaper(t_cube3d *cube3d, int32_t floor_color,
					int32_t ceiling_color);

// init
void			initialize(t_cube3d *cube3d);
void			start_params(t_cube3d *cube3d);

// util
char		 	*remove_new_line(char *str);

// validation
char			*valid_args(int argc, char **argv);
void			valid_map(t_cube3d *cube3d);
char			*valid_charset(char *str, char *set);

// read_param
size_t			parse_parameters(t_cube3d *cube3d, int fd);

#endif
