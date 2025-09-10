/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:41:04 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/10 17:30:52 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_boss_pixel(t_game *game, t_image *frame,
					t_point screen_data, t_pixel pixel)
{
	int	tex_x;
	int	tex_y;
	int	color;

	if (pixel.screen_x < 0 || pixel.screen_x >= WIN_WIDTH
		|| pixel.screen_y < 0 || pixel.screen_y >= WIN_HEIGHT)
		return ;
	if (screen_data.size <= 0)
		return ;
	tex_x = pixel.sprite_x * frame->width / screen_data.size;
	tex_y = pixel.sprite_y * frame->height / screen_data.size;
	if (tex_x >= frame->width)
		tex_x = frame->width - 1;
	if (tex_y >= frame->height)
		tex_y = frame->height - 1;
	color = *(int *)(frame->addr + (tex_y * frame->line_len
				+ tex_x * (frame->bpp / 8)));
	if ((unsigned int)color != 0x000000 && (unsigned int)color != 0xFF000000
		&& screen_data.dist < game->z_buffer[pixel.screen_x])
	{
		*(int *)(game->buffer.addr + (pixel.screen_y * game->buffer.line_len
					+ pixel.screen_x * (game->buffer.bpp / 8))) = color;
	}
}

static void	draw_boss_row(t_game *game, t_point screen_data,
					t_pixel *pixel, int start_x)
{
	int	start_y;

	start_y = WIN_HEIGHT / 2 - screen_data.size / 2;
	pixel->sprite_x = -1;
	while (++pixel->sprite_x < screen_data.size
		&& start_x + pixel->sprite_x < WIN_WIDTH)
	{
		if (start_x + pixel->sprite_x >= 0)
		{
			pixel->screen_x = start_x + pixel->sprite_x;
			pixel->screen_y = start_y + pixel->sprite_y;
			draw_boss_pixel(game, &game->boss.frames[game->boss.frame],
				screen_data, *pixel);
		}
	}
}

void	draw_boss_sprite(t_game *game, t_point screen_data)
{
	t_pixel	pixel;
	int		start_x;
	int		start_y;

	start_x = screen_data.x - screen_data.size / 2;
	start_y = WIN_HEIGHT / 2 - screen_data.size / 2;
	pixel.sprite_y = -1;
	while (++pixel.sprite_y < screen_data.size
		&& start_y + pixel.sprite_y < WIN_HEIGHT)
	{
		if (start_y + pixel.sprite_y >= 0)
			draw_boss_row(game, screen_data, &pixel, start_x);
	}
}
