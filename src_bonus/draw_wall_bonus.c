/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:31:07 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/03 20:22:32 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	calculate_boss_screen_pos(t_game *game, t_point *screen_data)
{
	double	dx;
	double	dy;
	double	angle;

	if (!game->boss.active)
		return (0);
	dx = game->boss.x - game->player_x;
	dy = game->boss.y - game->player_y;
	screen_data->distance = sqrt(dx * dx + dy * dy);
	if (screen_data->distance > 10.0)
		return (0);
	angle = atan2(dy, dx) - atan2(game->dir_y, game->dir_x);
	while (angle > M_PI)
		angle -= 2 * M_PI;
	while (angle < -M_PI)
		angle += 2 * M_PI;
	if (angle > M_PI / 3 || angle < -M_PI / 3)
		return (0);
	screen_data->x = (int)(WIN_WIDTH / 2 * (1 + angle / (M_PI / 3)));
	screen_data->size = (int)(WIN_HEIGHT / screen_data->distance * 0.5);
	return (1);
}

void	render_boss(t_game *game)
{
	t_point	screen_data;

	if (calculate_boss_screen_pos(game, &screen_data))
		draw_boss_sprite(game, screen_data);
}

int	render_buffer(t_game *game)
{
	game->buffer.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->buffer.img)
		return (ft_error("Failed to create render buffer"));
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bpp,
			&game->buffer.line_len,
			&game->buffer.endian);
	if (!game->buffer.addr)
		return (ft_error("Failed to get buffer address"));
	game->buffer.width = WIN_WIDTH;
	game->buffer.height = WIN_HEIGHT;
	return (0);
}

static void	wall_column(t_game *game, int screen_x, t_hit hit, int wall[4])
{
	int	y;
	int	tex_y;
	int	color;
	int	tex_x;

	tex_x = wall[3];
	y = wall[0];
	while (y <= wall[1] && y < WIN_HEIGHT)
	{
		if (y >= 0 && screen_x >= 0 && screen_x < WIN_WIDTH)
		{
			if (wall[2] > 0)
				tex_y = (y - wall[0]) * hit.txtr->height / wall[2];
			else
				tex_y = 0;
			if (tex_y >= hit.txtr->height)
				tex_y = hit.txtr->height - 1;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_x >= 0 && tex_x < hit.txtr->width)
			{
				color = *(int *)(hit.txtr->addr
						+ (tex_y * hit.txtr->line_len + tex_x * (hit.txtr->bpp / 8)));
				*(int *)(game->buffer.addr + (y * game->buffer.line_len
							+ screen_x * (game->buffer.bpp / 8))) = color;
			}
		}
		y++;
	}
}

void	draw_wall(t_game *game, int screen_x, t_hit hit)
{
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	wall_params[4];
	int	tex_x;

	if (!hit.txtr || !hit.txtr->addr || hit.dis <= 0.001 ||
		screen_x < 0 || screen_x >= WIN_WIDTH)
		return ;
	wall_height = (int)(WIN_HEIGHT / hit.dis);
	wall_top = (WIN_HEIGHT - wall_height) / 2;
	wall_bottom = wall_top + wall_height;
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= WIN_HEIGHT)
		wall_bottom = WIN_HEIGHT - 1;
	tex_x = (int)(hit.hit_p * hit.txtr->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= hit.txtr->width)
		tex_x = hit.txtr->width - 1;
	wall_params[0] = wall_top;
	wall_params[1] = wall_bottom;
	wall_params[2] = wall_height;
	wall_params[3] = tex_x;
	wall_column(game, screen_x, hit, wall_params);
}
