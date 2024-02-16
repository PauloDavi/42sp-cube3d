/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:28:28 by paulo             #+#    #+#             */
/*   Updated: 2024/02/15 21:10:49 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
		exit(EXIT_FAILURE);
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

size_t	find_max_map_width(t_cube3d *cube3d)
{
	size_t	i;
	size_t	j;
	size_t	max;

	i = 0;
	max = 0;
	while (i < cube3d->map_y)
	{
		j = 0;
		while (cube3d->map[i][j] != '\0' && cube3d->map[i][j] != '\n')
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}
