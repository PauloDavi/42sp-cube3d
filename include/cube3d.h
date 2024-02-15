/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:54 by paulo             #+#    #+#             */
/*   Updated: 2024/02/14 20:29:30 by bedos-sa         ###   ########.fr       */
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
# define PLAYER_SPEED 0.03

# define PLAYER_COLOR 0x00FF00FF
# define WALL_COLOR 0x000000FF
# define EMPTY_COLOR 0xFFFFFFFF

# define VALID_CHAR_SET "01NSEW\n "
# define VALID_CHAR_SET_PLAYER "NSEW"
# define FILE_EXTENSION ".cub"

# define WEST "WE"
# define NORTH "NO"
# define EAST "EA"
# define SOUTH "SO"
# define FLOOR "F"
# define CEILING "C"

# define ERR_INVALID_CHAR "Error\nInvalid map char '%d'\n"
# define ERR_INVALID_PLAYER "Error\nInvalid number of players '%d'\n"
# define ERR_INVALID_TEXTURE_COLOR "Error\nInvalid map texture or map color\n"
# define ERR_INVALID_PARAMETER "Error\nInvalid parameter\n"
# define ERR_INVALID_COLOR_QUANT "Error\nInvalid number of colors\n"
# define ERR_INVALID_TEXTURE "Error\nInvalid map texture\n"
# define ERR_INVALID_DUPLICATED_COLOR "Error\nInvalid duplicated color\n"
# define ERR_INVALID_COLOR "Error\nInvalid color\n"
# define ERR_INVALID_DUPLICATED_TEXTURE "Error\nInvalid duplicated texture\n"
# define ERR_INVALID_MAP_FILE "Error\nInvalid map file\n"
# define ERR_INVALID_EMPTY_FILE "Error\nEmpty file\n"
# define ERR_INVALID_MALLOC "Error\nMalloc error\n"
# define ERR_INVALID_OPEN_MAP "Error\nOpen map\n"
# define ERR_INVALID_ARG_NUM "Error\nInvalid number of arguments\n"
# define ERR_INVALID_FILE_NAME "Error\nInvalid filename\n"
# define ERR_MISSING_PARAMS "Error\nMissing parameters\n"
# define ERR_MAP_NOT_FOUND "Error\nMap not found\n"

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_cube3d
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*image;
	char			**map;
	size_t			map_y;
	t_vector		player;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	int64_t			floor_color;
	int64_t			ceiling_color;
}					t_cube3d;

// finish
void				free_for_finish(t_cube3d *cube3d);
void				err_exit(char *str);
void				close_err_exit(int fd, char *str);
void				close_free_err_exit(int fd, char **arr, char *err_message);
void				free_texture(t_cube3d *cube3d);

// map
void				read_map(t_cube3d *cube3d, char *map_file);
void				draw_mini_map(t_cube3d *cube3d);
void				get_player_position(t_cube3d *cube3d, char *line,
						size_t current_y);

// draw
void				draw_square(t_cube3d *cube3d, t_vector *point, size_t size,
						int32_t color);
void				draw_circle(t_cube3d *cube3d, t_vector *center, int radius,
						int32_t color);
void				draw_wallpaper(t_cube3d *cube3d, int32_t floor_color,
						int32_t ceiling_color);

// init
void				initialize(t_cube3d *cube3d);
void				start_params(t_cube3d *cube3d);

// util
char				*remove_new_line(char *str);
bool				is_empty_line(char *str);
size_t				get_file_size(char *map_file);

// validation
char				*valid_args(int argc, char **argv);
void				valid_map(t_cube3d *cube3d);
char				*valid_charset(char *str, char *set);

// player
int					valid_player(char *line);

// read_param
size_t				parse_parameters(t_cube3d *cube3d, int fd, char **map_line);

#endif
