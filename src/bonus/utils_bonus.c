/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:28:28 by paulo             #+#    #+#             */
/*   Updated: 2024/03/11 21:04:17 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*remove_new_line(char *str)
{
	int		i;
	int		size;
	char	*line;

	i = 0;
	size = ft_strlen(str);
	line = malloc(size * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (i < size - 1)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	free(str);
	return (line);
}

bool	is_empty_line(char *str)
{
	return (valid_charset(str, " \n") == NULL);
}

size_t	get_file_size(char *map_file)
{
	char	*line;
	int		fd;
	size_t	lines_size;

	lines_size = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		err_exit(ERR_INVALID_MAP_FILE);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		lines_size++;
		free(line);
	}
	close(fd);
	return (lines_size);
}

size_t	find_max_map_width(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;
	size_t	max;

	i = 0;
	max = 0;
	while (i < cub3d->map_y)
	{
		j = 0;
		while (cub3d->map[i][j] != '\0' && cub3d->map[i][j] != '\n')
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

bool	has_load_all_params(t_cub3d *cub3d)
{
	return (cub3d->west_texture != NULL && cub3d->east_texture != NULL
		&& cub3d->south_texture != NULL && cub3d->south_texture != NULL
		&& cub3d->door_texture != NULL && cub3d->wall_door_texture != NULL
		&& cub3d->sprite_1_texture != NULL && cub3d->sprite_2_texture != NULL
		&& cub3d->sprite_3_texture != NULL && cub3d->ceiling_color != -1
		&& cub3d->floor_color != -1);
}
