/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:50:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/14 20:07:08 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	read_map(t_cube3d *cube3d, char *map_file)
{
	size_t	lines_size;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		err_exit(ERR_INVALID_MAP_FILE);
	lines_size = get_file_size(map_file);
	if (lines_size == 0)
		err_exit(ERR_INVALID_EMPTY_FILE);
	lines_size -= parse_parameters(cube3d, fd, &line);
	cube3d->map = malloc((lines_size + 1) * sizeof(char *));
	if (cube3d->map == NULL)
		err_exit(ERR_INVALID_MALLOC);
	cube3d->map[lines_size] = NULL;
	cube3d->map_y = lines_size;
	lines_size = 0;
	while (true)
	{
		cube3d->map[lines_size++] = line;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	close(fd);
}

void	get_player_position(t_cube3d *cube3d, char *line, size_t current_y)
{
	char	*ptr;

	ptr = ft_strchr(line, 'N');
	if (ptr == NULL)
	{
		ptr = ft_strchr(line, 'S');
		if (ptr == NULL)
		{
			ptr = ft_strchr(line, 'E');
			if (ptr == NULL)
				ptr = ft_strchr(line, 'W');
		}
	}
	if (ptr != NULL)
	{
		cube3d->player.x = ptr - line;
		cube3d->player.y = current_y;
		*ptr = '0';
	}
}
