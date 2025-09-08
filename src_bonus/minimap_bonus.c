/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:35:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/08 13:16:23 by hbousset         ###   ########.fr       */
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

static void	draw_square(t_game *game, t_square sq)
{
	int	x;
	int	y;
	int	*pixel;

	y = sq.y;
	while (y < sq.y + sq.scale && y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = sq.x;
		while (x < sq.x + sq.scale && x < MINIMAP_X + MINIMAP_SIZE)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			{
				pixel = (int *)(game->buffer.addr + (y * game->buffer.line_len
							+ x * (game->buffer.bpp / 8)));
				*pixel = sq.color;
			}
			x++;
		}
		y++;
	}
}

static int	get_cell_color(t_game *game, int map_y, int map_x)
{
	if (map_y < 0 || map_y >= game->map_height ||
		map_x < 0 || map_x >= game->map_width)
		return (0x000000);
	if (!game->map[map_y])
		return (0x000000);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (0x000000);
	if (game->map[map_y][map_x] == '1')
		return (0x808080);
	else if (game->map[map_y][map_x] == ' ')
		return ((game->c_color[0] << 16)
			| (game->c_color[1] << 8) | game->c_color[2]);
	else
		return (0xFFFFFF);
}

static void	draw_map_grid(t_game *game, int scale)
{
	int			map_x;
	int			map_y;
	t_square	sq;

	map_y = 0;
	while (map_y < game->map_height && map_y * scale < MINIMAP_SIZE)
	{
		map_x = 0;
		while (map_x < game->map_width && map_x * scale < MINIMAP_SIZE)
		{
			sq.x = MINIMAP_X + map_x * scale;
			sq.y = MINIMAP_Y + map_y * scale;
			sq.color = get_cell_color(game, map_y, map_x);
			sq.scale = scale;
			draw_square(game, sq);
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_point	p;
	t_point	boss_p;

	p.scale = minimap_scale(game);
	p.x = MINIMAP_X + (int)(game->player_x * p.scale);
	p.y = MINIMAP_Y + (int)(game->player_y * p.scale);
	boss_p.x = MINIMAP_X + (int)(game->boss.x * p.scale);
	boss_p.y = MINIMAP_Y + (int)(game->boss.y * p.scale);
	draw_map_grid(game, p.scale);
	draw_minimap_entity(game, p, 0XFF0000);
	if (game->boss.active)
		draw_minimap_entity(game, boss_p, 0xFF00FF);
}
