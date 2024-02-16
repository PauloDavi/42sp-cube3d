/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:49:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/15 20:29:03 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		check_params_map(t_cube3d *cube3d, int fd, char *str);
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
			break ;
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
