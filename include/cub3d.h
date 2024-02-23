/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:26:54 by paulo             #+#    #+#             */
/*   Updated: 2024/02/19 22:23:06 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
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
# define PLAYER_ROTATE_SPEED 0.03

# define PLAYER_COLOR 0x00FFFFFF
# define WALL_COLOR 0x000000FF
# define EMPTY_COLOR 0xFFFFFFFF
# define RAY_COLOR 0xFF0000FF

# define VALID_CHAR_SET "01NSEW\n "
# define NOT_PLAYER_CHAR_SET "01 "
# define VALID_CHAR_SET_PLAYER "NSEW"
# define VALID_WALLS_CHAR_SET "1 "
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

typedef struct s_cub3d
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*image;
	char			**map;
	size_t			map_x;
	size_t			map_y;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	int64_t			floor_color;
	int64_t			ceiling_color;
	t_vector		player;
	t_vector		dir;
	t_vector		plane;
}					t_cub3d;

// finish
void				free_for_finish(t_cub3d *cub3d);
void				err_exit(char *str);
void				close_err_exit(int fd, char *str);
void				close_free_err_exit(int fd, char **arr, char *err_message);
void				free_texture(t_cub3d *cub3d);

// map
void				read_map(t_cub3d *cub3d, char *map_file);
void				draw_mini_map(t_cub3d *cub3d);
void				get_player_position(t_cub3d *cub3d, char *line,
						size_t current_y);
void				normalize_map(t_cub3d *cub3d);

// draw
void				draw_square(t_cub3d *cub3d, t_vector *point, size_t size,
						int32_t color);
void				draw_circle(t_cub3d *cub3d, t_vector *center, int radius,
						int32_t color);
void				draw_wallpaper(t_cub3d *cub3d, int32_t floor_color,
						int32_t ceiling_color);
void				draw_center_vertical_line(t_cub3d *cub3d, int x, int length,
						int color);
void				draw_line(t_cub3d *cub3d, t_vector *point1,
						t_vector *point2, int color);

// init
void				initialize(t_cub3d *cub3d);
void				start_params(t_cub3d *cub3d);

// util
char				*remove_new_line(char *str);
bool				is_empty_line(char *str);
size_t				get_file_size(char *map_file);
size_t				find_max_map_width(t_cub3d *cub3d);

// validation
char				*valid_args(int argc, char **argv);
void				valid_map(t_cub3d *cub3d);
char				*valid_charset(char *str, char *set);

// player
int					valid_player(char *line);

// read_param
size_t				parse_parameters(t_cub3d *cub3d, int fd, char **map_line);

// load_params
void				load_texture(t_cub3d *cub3d, mlx_texture_t **texture,
						int fd, char **words);
void				load_color(t_cub3d *cub3d, int64_t *color, int fd,
						char **words);

#endif
