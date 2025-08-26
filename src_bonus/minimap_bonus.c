/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:35:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/25 15:12:45 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	calculate_minimap_scale(t_game *game)
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

static void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	int	*pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = (int *)(game->buffer.addr + (y * game->buffer.line_len
					+ x * (game->buffer.bpp / 8)));
		*pixel = color;
	}
}

static void	draw_square(t_game *game, int start_x, int start_y, int color, int scale)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + scale && y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = start_x;
		while (x < start_x + scale && x < MINIMAP_X + MINIMAP_SIZE)
		{
			put_pixel_minimap(game, x, y, color);
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

	scale = calculate_minimap_scale(game);
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
	int	player_screen_x;
	int	player_screen_y;
	int	x;
	int	y;
	int	scale;

	scale = calculate_minimap_scale(game);
	player_screen_x = MINIMAP_X + (int)(game->player_x * scale);
	player_screen_y = MINIMAP_Y + (int)(game->player_y * scale);

	y = player_screen_y - PLAYER_SIZE;
	while (y <= player_screen_y + PLAYER_SIZE)
	{
		x = player_screen_x - PLAYER_SIZE;
		while (x <= player_screen_x + PLAYER_SIZE)
		{
			put_pixel_minimap(game, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_fov_lines(t_game *game)
{
	int		i;
	double	ray_x;
	double	ray_y;
	int		line_x;
	int		line_y;
	int		player_screen_x;
	int		player_screen_y;
	int		scale;

	scale = calculate_minimap_scale(game);
	player_screen_x = MINIMAP_X + (int)(game->player_x * scale);
	player_screen_y = MINIMAP_Y + (int)(game->player_y * scale);

	i = 0;
	while (i < FOV_LINES)
	{
		double camera_x = 2.0 * i / FOV_LINES - 1.0;
		ray_x = game->dir_x + game->plane_x * camera_x;
		ray_y = game->dir_y + game->plane_y * camera_x;
		line_x = player_screen_x + (int)(ray_x * 30);
		line_y = player_screen_y + (int)(ray_y * 30);
		double dx = line_x - player_screen_x;
		double dy = line_y - player_screen_y;
		double steps = fmax(fabs(dx), fabs(dy));
		if (steps > 0)
		{
			dx /= steps;
			dy /= steps;

			double x = player_screen_x;
			double y = player_screen_y;
			int j = 0;
			while (j <= (int)steps)
			{
				put_pixel_minimap(game, (int)x, (int)y, 0x00FF00);
				x += dx;
				y += dy;
				j++;
			}
		}
		i += 5;
	}
}

void	draw_minimap(t_game *game)
{
	draw_map_grid(game);
	draw_fov_lines(game);
	draw_player_dot(game);
}
