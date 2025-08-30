/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:31:07 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/30 17:45:09 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	update_boss(t_game *game)
{
	if (!game->boss.active)
		return ;
	game->boss.counter++;
	if (game->boss.counter >= game->boss.delay)
	{
		game->boss.frame = (game->boss.frame + 1) % 6;
		game->boss.counter = 0;
	}
	move_boss_towards_player(game);
	check_boss_collision(game);
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
	while (y <= wall[1])
	{
		tex_y = (y - wall[0]) * hit.txtr->height / wall[2];
		if (tex_y >= hit.txtr->height)
			tex_y = hit.txtr->height - 1;
		color = *(int *)(hit.txtr->addr
				+ (tex_y * hit.txtr->line_len + tex_x * (hit.txtr->bpp / 8)));
		*(int *)(game->buffer.addr + (y * game->buffer.line_len
					+ screen_x * (game->buffer.bpp / 8))) = color;
		y++;
	}
}

void	draw_wall(t_game *game, int screen_x, t_hit hit)
{
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	wall_params[4];

	if (!hit.txtr || !hit.txtr->addr || hit.dis <= 0.001)
		return ;
	wall_height = (int)(WIN_HEIGHT / hit.dis);
	wall_top = (WIN_HEIGHT - wall_height) / 2;
	wall_bottom = wall_top + wall_height;
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= WIN_HEIGHT)
		wall_bottom = WIN_HEIGHT - 1;
	wall_params[0] = wall_top;
	wall_params[1] = wall_bottom;
	wall_params[2] = wall_height;
	wall_params[3] = (int)(hit.hit_p * hit.txtr->width) % hit.txtr->width;
	wall_column(game, screen_x, hit, wall_params);
}
