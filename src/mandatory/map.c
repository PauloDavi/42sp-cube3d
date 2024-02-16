/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:50:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/15 21:11:10 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static size_t	get_end_empty_lines(t_cube3d *cube3d);
static void		clean_lines(t_cube3d *cube3d, size_t max_width);

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

void	normalize_map(t_cube3d *cube3d)
{
	size_t	max_width;
	size_t	empty_lines;
	char	**new_map;

	max_width = find_max_map_width(cube3d);
	clean_lines(cube3d, max_width);
	empty_lines = get_end_empty_lines(cube3d);
	if (empty_lines == 0)
		return ;
	cube3d->map_y -= empty_lines;
	new_map = malloc((cube3d->map_y + 1) * sizeof(char *));
	if (new_map == NULL)
		err_exit(ERR_INVALID_MALLOC);
	new_map[cube3d->map_y] = NULL;
	ft_memcpy(new_map, cube3d->map, cube3d->map_y * sizeof(char *));
	while (empty_lines--)
		free(cube3d->map[cube3d->map_y + empty_lines]);
	free(cube3d->map);
	cube3d->map = new_map;
}

static void	clean_lines(t_cube3d *cube3d, size_t max_width)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	while (i < cube3d->map_y)
	{
		j = 0;
		while (cube3d->map[i][j] != '\0' && cube3d->map[i][j] != '\n')
			j++;
		new_line = malloc((max_width + 1) * sizeof(char));
		if (new_line == NULL)
			err_exit(ERR_INVALID_MALLOC);
		new_line[max_width] = '\0';
		ft_memset(new_line, ' ', max_width);
		ft_memcpy(new_line, cube3d->map[i], j);
		free(cube3d->map[i]);
		cube3d->map[i] = new_line;
		i++;
	}
}

static size_t	get_end_empty_lines(t_cube3d *cube3d)
{
	size_t	i;

	i = cube3d->map_y - 1;
	while (i > 0)
	{
		if (!is_empty_line(cube3d->map[i]))
			return (cube3d->map_y - i - 1);
		i--;
	}
	return (0);
}
