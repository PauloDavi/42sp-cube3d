/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_param_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:49:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/03/11 19:51:51 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		check_params_map(t_cub3d *cub3d, int fd, char *str);
static size_t	skip_empty_lines(t_cub3d *cub3d, int fd, char **line);

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
		if (has_load_all_params(cub3d))
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
	else if (load_extra_texture(cub3d, words, fd))
		;
	else if (!ft_strncmp(words[0], FLOOR, 2))
		load_color(cub3d, &cub3d->floor_color, fd, words);
	else if (!ft_strncmp(words[0], CEILING, 2))
		load_color(cub3d, &cub3d->ceiling_color, fd, words);
	else
		invalid_parameter_exit(cub3d, fd, words, ERR_INVALID_TEXTURE_COLOR);
}
