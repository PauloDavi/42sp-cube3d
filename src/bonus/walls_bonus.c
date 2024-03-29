/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:13:00 by paulo             #+#    #+#             */
/*   Updated: 2024/03/11 22:40:03 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_tex_wall(t_cub3d *cub3d, t_ray_calc *ray_calc,
					t_draw_wall *draw_wall, mlx_texture_t *texture);

void	draw_center_vertical_line(t_cub3d *cub3d, t_ray_calc *ray_calc,
		mlx_texture_t *texture)
{
	t_draw_wall	draw_wall;

	if (ray_calc->side == 0)
		draw_wall.wall_x = cub3d->player.y + ray_calc->perp_wall_dist
			* ray_calc->ray.y;
	else
		draw_wall.wall_x = cub3d->player.x + ray_calc->perp_wall_dist
			* ray_calc->ray.x;
	draw_wall.wall_x -= floor(draw_wall.wall_x);
	draw_wall.tex_x = (int)(draw_wall.wall_x * (double)(texture->width));
	draw_wall.line_height = (int)(cub3d->mlx_ptr->height
			/ ray_calc->perp_wall_dist);
	draw_wall.draw_start = -draw_wall.line_height / 2 + cub3d->mlx_ptr->height
		/ 2;
	if (draw_wall.draw_start < 0)
		draw_wall.draw_start = 0;
	draw_wall.draw_end = draw_wall.line_height / 2 + cub3d->mlx_ptr->height / 2;
	if (draw_wall.draw_end >= cub3d->mlx_ptr->height)
		draw_wall.draw_end = cub3d->mlx_ptr->height - 1;
	draw_wall.step = (double)texture->height / draw_wall.line_height;
	draw_wall.tex_pos = (draw_wall.draw_start - cub3d->mlx_ptr->height / 2
			+ draw_wall.line_height / 2) * draw_wall.step;
	draw_tex_wall(cub3d, ray_calc, &draw_wall, texture);
}

static void	draw_tex_wall(t_cub3d *cub3d, t_ray_calc *ray_calc,
		t_draw_wall *draw_wall, mlx_texture_t *texture)
{
	int	y;

	y = draw_wall->draw_start;
	while (y < draw_wall->draw_end)
	{
		draw_wall->tex_y = (int)draw_wall->tex_pos;
		if (draw_wall->tex_y > (int)texture->height - 1)
			draw_wall->tex_y = texture->height - 1;
		draw_wall->tex_pos += draw_wall->step;
		draw_wall->color = rgb_to_int(&texture->pixels[(texture->height
					* draw_wall->tex_y + draw_wall->tex_x)
				* texture->bytes_per_pixel]);
		mlx_put_pixel(cub3d->image, ray_calc->x, y, draw_wall->color);
		y++;
	}
}

mlx_texture_t	*get_texture(t_cub3d *cub3d, t_ray_calc *ray_calc, double ray,
		bool is_x)
{
	if (ray_calc->is_door)
		return (cub3d->door_texture);
	else if (ray_calc->is_door_wall)
		return (cub3d->wall_door_texture);
	else if (ray > 0 && is_x)
		return (cub3d->east_texture);
	else if (ray < 0 && is_x)
		return (cub3d->west_texture);
	else if (ray > 0 && !is_x)
		return (cub3d->south_texture);
	else
		return (cub3d->north_texture);
}
