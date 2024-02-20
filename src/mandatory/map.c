/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:50:55 by bedos-sa          #+#    #+#             */
/*   Updated: 2024/02/20 18:18:06 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_end_empty_lines(t_cub3d *cub3d);
static void		clean_lines(t_cub3d *cub3d, size_t max_width);

void	read_map(t_cub3d *cub3d, char *map_file)
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
	lines_size -= parse_parameters(cub3d, fd, &line);
	cub3d->map = malloc((lines_size + 1) * sizeof(char *));
	if (cub3d->map == NULL)
		err_exit(ERR_INVALID_MALLOC);
	cub3d->map[lines_size] = NULL;
	cub3d->map_y = lines_size;
	lines_size = 0;
	while (true)
	{
		cub3d->map[lines_size++] = line;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	close(fd);
}

void	get_player_position(t_cub3d *cub3d, char *line, size_t current_y)
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
		cub3d->player.x = ptr - line;
		cub3d->player.y = current_y;
		*ptr = '0';
	}
}

void	normalize_map(t_cub3d *cub3d)
{
	size_t	max_width;
	size_t	empty_lines;
	char	**new_map;

	max_width = find_max_map_width(cub3d);
	clean_lines(cub3d, max_width);
	empty_lines = get_end_empty_lines(cub3d);
	if (empty_lines == 0)
		return ;
	cub3d->map_y -= empty_lines;
	new_map = malloc((cub3d->map_y + 1) * sizeof(char *));
	if (new_map == NULL)
		err_exit(ERR_INVALID_MALLOC);
	new_map[cub3d->map_y] = NULL;
	ft_memcpy(new_map, cub3d->map, cub3d->map_y * sizeof(char *));
	while (empty_lines--)
		free(cub3d->map[cub3d->map_y + empty_lines]);
	free(cub3d->map);
	cub3d->map = new_map;
}

static void	clean_lines(t_cub3d *cub3d, size_t max_width)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	while (i < cub3d->map_y)
	{
		j = 0;
		while (cub3d->map[i][j] != '\0' && cub3d->map[i][j] != '\n')
			j++;
		new_line = malloc((max_width + 1) * sizeof(char));
		if (new_line == NULL)
			err_exit(ERR_INVALID_MALLOC);
		new_line[max_width] = '\0';
		ft_memset(new_line, ' ', max_width);
		ft_memcpy(new_line, cub3d->map[i], j);
		free(cub3d->map[i]);
		cub3d->map[i] = new_line;
		i++;
	}
}

static size_t	get_end_empty_lines(t_cub3d *cub3d)
{
	size_t	i;

	i = cub3d->map_y - 1;
	while (i > 0)
	{
		if (!is_empty_line(cub3d->map[i]))
			return (cub3d->map_y - i - 1);
		i--;
	}
	return (0);
}
