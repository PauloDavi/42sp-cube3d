/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:49:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/14 21:04:28 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		check_params_map(t_cube3d *cube3d, int fd, char *str);
static void		load_texture(t_cube3d *cube3d, mlx_texture_t **texture, int fd,
					char **words);
static void		load_color(t_cube3d *cube3d, int64_t *color, int fd,
					char **words);
static uint32_t	parse_color(char **colors, t_cube3d *cube3d, int fd,
					char **words);
static size_t	skip_empty_lines(t_cube3d *cube3d, int fd, char **line);

size_t	parse_parameters(t_cube3d *cube3d, int fd, char **map_line)
{
	char	*line;
	size_t	read_lines;

	read_lines = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free_texture(cube3d);
			close_err_exit(fd, ERR_MISSING_PARAMS);
		}
		read_lines++;
		line = remove_new_line(line);
		if (!is_empty_line(line))
			check_params_map(cube3d, fd, line);
		free(line);
		if (cube3d->south_texture != NULL && cube3d->south_texture != NULL
			&& cube3d->west_texture != NULL && cube3d->east_texture != NULL
			&& cube3d->ceiling_color != -1 && cube3d->floor_color != -1)
			break ;
	}
	return (read_lines + skip_empty_lines(cube3d, fd, map_line));
}

static size_t	skip_empty_lines(t_cube3d *cube3d, int fd, char **line)
{
	size_t	num;

	num = 0;
	while (true)
	{
		*line = get_next_line(fd);
		if (*line == NULL)
		{
			free_texture(cube3d);
			close_err_exit(fd, ERR_MAP_NOT_FOUND);
		}
		if (!is_empty_line(*line))
			break;
		free(*line);
		num++;
	}
	return (num);
}

static void	check_params_map(t_cube3d *cube3d, int fd, char *str)
{
	char	**words;
	size_t	size;

	words = ft_split_size(str, ' ', &size);
	if (size != 2)
		close_free_err_exit(fd, words, ERR_INVALID_PARAMETER);
	if (!ft_strncmp(words[0], NORTH, 3))
		load_texture(cube3d, &cube3d->north_texture, fd, words);
	else if (!ft_strncmp(words[0], SOUTH, 3))
		load_texture(cube3d, &cube3d->south_texture, fd, words);
	else if (!ft_strncmp(words[0], WEST, 3))
		load_texture(cube3d, &cube3d->west_texture, fd, words);
	else if (!ft_strncmp(words[0], EAST, 3))
		load_texture(cube3d, &cube3d->east_texture, fd, words);
	else if (!ft_strncmp(words[0], FLOOR, 2))
		load_color(cube3d, &cube3d->floor_color, fd, words);
	else if (!ft_strncmp(words[0], CEILING, 2))
		load_color(cube3d, &cube3d->ceiling_color, fd, words);
	else
	{
		free_texture(cube3d);
		close_free_err_exit(fd, words, ERR_INVALID_TEXTURE_COLOR);
	}
}

static void	load_texture(t_cube3d *cube3d, mlx_texture_t **texture, int fd,
		char **words)
{
	if (*texture != NULL)
	{
		free_texture(cube3d);
		close_free_err_exit(fd, words, ERR_INVALID_DUPLICATED_TEXTURE);
	}
	*texture = mlx_load_png(words[1]);
	if (*texture == NULL)
	{
		free_texture(cube3d);
		close_free_err_exit(fd, words, ERR_INVALID_TEXTURE);
	}
}

static void	load_color(t_cube3d *cube3d, int64_t *color, int fd, char **words)
{
	size_t	size;
	char	**colors;

	if (*color != -1)
	{
		free_texture(cube3d);
		close_free_err_exit(fd, words, ERR_INVALID_DUPLICATED_COLOR);
	}
	colors = ft_split_size(words[1], ',', &size);
	if (size != 3)
	{
		ft_free_split(colors);
		free_texture(cube3d);
		close_free_err_exit(fd, words, ERR_INVALID_COLOR_QUANT);
	}
	*color = parse_color(colors, cube3d, fd, words);
	ft_free_split(colors);
}

static uint32_t	parse_color(char **colors, t_cube3d *cube3d, int fd,
		char **words)
{
	size_t		i;
	u_int32_t	color;
	int			current_color;
	bool		has_err;

	i = 0;
	color = 0;
	while (i < 3)
	{
		current_color = ft_safe_atoi(colors[i], &has_err);
		if (current_color < 0 || current_color > 0xFFFFFF || has_err)
		{
			ft_free_split(colors);
			free_texture(cube3d);
			close_free_err_exit(fd, words, ERR_INVALID_COLOR);
		}
		color = (color << 8) | current_color;
		i++;
	}
	color = (color << 8) | 0xFF;
	return (color);
}
