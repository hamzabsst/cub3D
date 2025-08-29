/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:35:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 10:14:32 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	minimap_scale(t_game *game)
{
	int	scale_x;
	int	scale_y;
	int	scale;

	if (game->map_width == 0 || game->map_height == 0)
		return (8);
	scale_x = MINIMAP_SIZE / game->map_width;
	scale_y = MINIMAP_SIZE / game->map_height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 3)
		scale = 3;
	if (scale > 12)
		scale = 12;
	return (scale);
}

static void	draw_square(t_game *game, int start_x, int start_y, int color, int scale)
{
	int	x;
	int	y;
	int	*pixel;

	y = start_y;
	while (y < start_y + scale && y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = start_x;
		while (x < start_x + scale && x < MINIMAP_X + MINIMAP_SIZE)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			{
				pixel = (int *)(game->buffer.addr + (y * game->buffer.line_len
					+ x * (game->buffer.bpp / 8)));
				*pixel = color;
			}
			x++;
		}
		y++;
	}
}

static void	draw_map_grid(t_game *game)
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	color;
	int	scale;

	scale = minimap_scale(game);
	map_y = 0;
	while (map_y < game->map_height && map_y * scale < MINIMAP_SIZE)
	{
		map_x = 0;
		while (map_x < game->map_width && map_x * scale < MINIMAP_SIZE)
		{
			screen_x = MINIMAP_X + map_x * scale;
			screen_y = MINIMAP_Y + map_y * scale;
			if (map_y < game->map_height && map_x < (int)ft_strlen(game->map[map_y]))
			{
				if (game->map[map_y][map_x] == '1')
					color = 0x808080;
				else if (game->map[map_y][map_x] == ' ')
					color = game->c_color[0] << 16 | (game->c_color[1] << 8) | game->c_color[2];
				else
					color = 0xFFFFFF;
			}
			else
				color = 0x000000;
			draw_square(game, screen_x, screen_y, color, scale);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player_dot(t_game *game)
{
	int	player_x;
	int	player_y;
	int	x;
	int	y;
	int	scale;
	int	*pixel;

	scale = minimap_scale(game);
	player_x = MINIMAP_X + (int)(game->player_x * scale);
	player_y = MINIMAP_Y + (int)(game->player_y * scale);

	y = player_y - PLAYER_SIZE;
	while (y <= player_y + PLAYER_SIZE)
	{
		x = player_x - PLAYER_SIZE;
		while (x <= player_x + PLAYER_SIZE)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			{
				pixel = (int *)(game->buffer.addr + (y * game->buffer.line_len
					+ x * (game->buffer.bpp / 8)));
				*pixel = 0XFF0000;
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_map_grid(game);
	draw_player_dot(game);
}
