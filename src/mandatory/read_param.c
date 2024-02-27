/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:49:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/26 22:33:07 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		check_params_map(t_cub3d *cub3d, int fd, char *str);
static size_t	skip_empty_lines(t_cub3d *cub3d, int fd, char **line);
static void		invalid_parameter_exit(t_cub3d *cub3d, int fd, char **words, char *str);

size_t	parse_parameters(t_cub3d *cub3d, int fd, char **map_line)
{
	char	*line;
	size_t	read_lines;

	read_lines = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free_texture(cub3d);
			close_err_exit(fd, ERR_MISSING_PARAMS);
		}
		read_lines++;
		line = remove_new_line(line);
		if (!is_empty_line(line))
			check_params_map(cub3d, fd, line);
		else
			free(line);
		if (cub3d->south_texture != NULL && cub3d->south_texture != NULL
			&& cub3d->west_texture != NULL && cub3d->east_texture != NULL
			&& cub3d->ceiling_color != -1 && cub3d->floor_color != -1)
			break ;
	}
	return (read_lines + skip_empty_lines(cub3d, fd, map_line));
}

static size_t	skip_empty_lines(t_cub3d *cub3d, int fd, char **line)
{
	size_t	num;

	num = 0;
	while (true)
	{
		*line = get_next_line(fd);
		if (*line == NULL)
		{
			free_texture(cub3d);
			close_err_exit(fd, ERR_MAP_NOT_FOUND);
		}
		if (!is_empty_line(*line))
			break ;
		free(*line);
		num++;
	}
	return (num);
}

static void	check_params_map(t_cub3d *cub3d, int fd, char *str)
{
	char	**words;
	size_t	size;

	words = ft_split_size(str, ' ', &size);
	free(str);
	if (size != 2)
		invalid_parameter_exit(cub3d, fd, words, ERR_INVALID_PARAMETER);
	if (!ft_strncmp(words[0], NORTH, 3))
		load_texture(cub3d, &cub3d->north_texture, fd, words);
	else if (!ft_strncmp(words[0], SOUTH, 3))
		load_texture(cub3d, &cub3d->south_texture, fd, words);
	else if (!ft_strncmp(words[0], WEST, 3))
		load_texture(cub3d, &cub3d->west_texture, fd, words);
	else if (!ft_strncmp(words[0], EAST, 3))
		load_texture(cub3d, &cub3d->east_texture, fd, words);
	else if (!ft_strncmp(words[0], FLOOR, 2))
		load_color(cub3d, &cub3d->floor_color, fd, words);
	else if (!ft_strncmp(words[0], CEILING, 2))
		load_color(cub3d, &cub3d->ceiling_color, fd, words);
	else
		invalid_parameter_exit(cub3d, fd, words, ERR_INVALID_TEXTURE_COLOR);
}

static void	invalid_parameter_exit(t_cub3d *cub3d, int fd, char **words, char *str)
{
	free_memory(fd);
	free_texture(cub3d);
	close_free_err_exit(fd, words, str);
}
