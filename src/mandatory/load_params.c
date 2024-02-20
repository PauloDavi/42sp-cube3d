/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 02:14:14 by paulo             #+#    #+#             */
/*   Updated: 2024/02/20 18:18:06 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	parse_color(char **colors, t_cub3d *cub3d, int fd,
					char **words);

void	load_texture(t_cub3d *cub3d, mlx_texture_t **texture, int fd,
		char **words)
{
	if (*texture != NULL)
	{
		free_texture(cub3d);
		close_free_err_exit(fd, words, ERR_INVALID_DUPLICATED_TEXTURE);
	}
	*texture = mlx_load_png(words[1]);
	if (*texture == NULL)
	{
		free_texture(cub3d);
		close_free_err_exit(fd, words, ERR_INVALID_TEXTURE);
	}
}

void	load_color(t_cub3d *cub3d, int64_t *color, int fd, char **words)
{
	size_t	size;
	char	**colors;

	if (*color != -1)
	{
		free_texture(cub3d);
		close_free_err_exit(fd, words, ERR_INVALID_DUPLICATED_COLOR);
	}
	colors = ft_split_size(words[1], ',', &size);
	if (size != 3)
	{
		ft_free_split(colors);
		free_texture(cub3d);
		close_free_err_exit(fd, words, ERR_INVALID_COLOR_QUANT);
	}
	*color = parse_color(colors, cub3d, fd, words);
	ft_free_split(colors);
}

static uint32_t	parse_color(char **colors, t_cub3d *cub3d, int fd,
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
			free_texture(cub3d);
			close_free_err_exit(fd, words, ERR_INVALID_COLOR);
		}
		color = (color << 8) | current_color;
		i++;
	}
	color = (color << 8) | 0xFF;
	return (color);
}
