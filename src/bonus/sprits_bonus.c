/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprits_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:54:42 by paulo             #+#    #+#             */
/*   Updated: 2024/03/11 22:15:33 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static mlx_texture_t	*select_texture(t_cub3d *cub3d, char c);

void	load_sprites(t_cub3d *cub3d)
{
	size_t		x;
	size_t		y;
	t_sprite	*sprite;

	y = 0;
	while (y < cub3d->map_y)
	{
		x = 0;
		while (x < cub3d->map_x)
		{
			if (cub3d->map[y][x] == '2' || cub3d->map[y][x] == '3'
				|| cub3d->map[y][x] == '4')
			{
				sprite = malloc(sizeof(t_sprite));
				sprite->position.x = x + 0.5;
				sprite->position.y = y + 0.5;
				sprite->texture = select_texture(cub3d, cub3d->map[y][x]);
				ft_lstadd_back(&cub3d->sprites_list, ft_lstnew(sprite));
				cub3d->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

static mlx_texture_t	*select_texture(t_cub3d *cub3d, char c)
{
	if (c == '2')
		return (cub3d->sprite_1_texture);
	else if (c == '3')
		return (cub3d->sprite_2_texture);
	else
		return (cub3d->sprite_3_texture);
}

void	calc_sprites_distance(t_cub3d *cub3d, t_sprite_calc *calc,
		t_sprite *sprite)
{
	calc->sprite_pos.x = sprite->position.x - cub3d->player.x;
	calc->sprite_pos.y = sprite->position.y - cub3d->player.y;
	calc->inv_det = 1.0 / (cub3d->plane.x * cub3d->dir.y - cub3d->dir.x
			* cub3d->plane.y);
	calc->transform.x = calc->inv_det * (cub3d->dir.y * calc->sprite_pos.x
			- cub3d->dir.x * calc->sprite_pos.y);
	calc->transform.y = calc->inv_det * (-cub3d->plane.y * calc->sprite_pos.x
			+ cub3d->plane.x * calc->sprite_pos.y);
	calc->sprite_screen_x = (cub3d->mlx_ptr->width / 2) * (1 + calc->transform.x
			/ calc->transform.y);
	calc->sprite_height = abs((int)(cub3d->mlx_ptr->height
				/ (calc->transform.y)));
	calc->draw_start_y = -calc->sprite_height / 2 + cub3d->mlx_ptr->height / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->sprite_height / 2 + cub3d->mlx_ptr->height / 2;
	if (calc->draw_end_y >= cub3d->mlx_ptr->height)
		calc->draw_end_y = cub3d->mlx_ptr->height - 1;
}

void	render_sprite(t_cub3d *cub3d, t_sprite_calc *c, t_sprite *sprite)
{
	while (c->draw_start_x < c->draw_end_x)
	{
		c->tex_x = (c->draw_start_x - (-c->sprite_width / 2 + \
			c->sprite_screen_x)) * sprite->texture->width / c->sprite_width;
		if (c->transform.y > 0 && c->draw_start_x > 0
			&& c->draw_start_x < cub3d->mlx_ptr->width
			&& c->transform.y < cub3d->z_buffer[c->draw_start_x])
		{
			c->y = c->draw_start_y;
			while (c->y < c->draw_end_y)
			{
				c->tex_y = ((c->y - (cub3d->mlx_ptr->height / 2)
							+ (c->sprite_height / 2)) * sprite->texture->height)
					/ c->sprite_height;
				c->color = rgb_to_int(&sprite->texture->pixels[\
					(sprite->texture->height * c->tex_y + c->tex_x)
						* sprite->texture->bytes_per_pixel]);
				if (c->color != 0x000000FF)
					mlx_put_pixel(cub3d->image, c->draw_start_x, \
					c->y, c->color);
				c->y++;
			}
		}
		c->draw_start_x++;
	}
}

void	draw_sprites(t_cub3d *cub3d)
{
	t_sprite_calc	calc;
	t_sprite		**arr;
	size_t			i;

	i = -1;
	arr = ft_lst_to_array(cub3d->sprites_list);
	sort_sprites(cub3d, arr);
	while (arr[++i] != NULL)
	{
		calc_sprites_distance(cub3d, &calc, arr[i]);
		calc.sprite_width = abs((int)(cub3d->mlx_ptr->height
					/ (calc.transform.y)));
		calc.draw_start_x = -calc.sprite_width / 2 + calc.sprite_screen_x;
		if (calc.draw_start_x < 0)
			calc.draw_start_x = 0;
		calc.draw_end_x = calc.sprite_width / 2 + calc.sprite_screen_x;
		if (calc.draw_end_x >= cub3d->mlx_ptr->width)
			calc.draw_end_x = cub3d->mlx_ptr->width - 1;
		render_sprite(cub3d, &calc, arr[i]);
	}
	free(arr);
}
