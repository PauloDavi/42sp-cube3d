/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprits_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:54:42 by paulo             #+#    #+#             */
/*   Updated: 2024/03/10 12:20:33 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_sprits(t_cub3d *cub3d)
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
			if (cub3d->map[y][x] == '4')
			{
				sprite = malloc(sizeof(t_sprite));
				sprite->position.x = x + 0.5;
				sprite->position.y = y + 0.5;
				sprite->texture = cub3d->sprite_texture;
				ft_lstadd_back(&cub3d->sprites_list, ft_lstnew(sprite));
				cub3d->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void	draw_sprits(t_cub3d *cub3d)
{
	t_list *lst;
	t_sprite *sprite;

	lst = cub3d->sprites_list;
	while (lst != NULL)
	{
		sprite = lst->content;
		double sprite_x = sprite->position.x - cub3d->player.x;
		double sprite_y = sprite->position.y - cub3d->player.y;
		double invDet = 1.0 / (cub3d->plane.x * cub3d->dir.y - cub3d->dir.x
				* cub3d->plane.y);
		double transformX = invDet * (cub3d->dir.y * sprite_x - cub3d->dir.x
				* sprite_y);
		double transformY = invDet * (-cub3d->plane.y * sprite_x
				+ cub3d->plane.x * sprite_y);
		int spriteScreenX = (int)((cub3d->mlx_ptr->width / 2) * (1 + transformX
					/ transformY));
		int spriteHeight = abs((int)(cub3d->mlx_ptr->height / (transformY)));
		int drawStartY = -spriteHeight / 2 + cub3d->mlx_ptr->height / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cub3d->mlx_ptr->height / 2;
		if (drawEndY >= cub3d->mlx_ptr->height)
			drawEndY = cub3d->mlx_ptr->height - 1;
		int spriteWidth = abs((int)(cub3d->mlx_ptr->height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= cub3d->mlx_ptr->width)
			drawEndX = cub3d->mlx_ptr->width - 1;
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX))
					* sprite->texture->width / spriteWidth);
			if (transformY > 0 && stripe > 0 && stripe < cub3d->mlx_ptr->width
				&& transformY < cub3d->z_buffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++)
				{
					int texY = ((y - (cub3d->mlx_ptr->height/2) + (spriteHeight/2)) * sprite->texture->height) / spriteHeight;
					int color = rgb_to_int(&sprite->texture->pixels[(sprite->texture->height * texY + texX) * sprite->texture->bytes_per_pixel]);
					if (color != 0x000000FF)
						mlx_put_pixel(cub3d->image, stripe, y, color);
				}
		}
		lst = lst->next;
	}
}