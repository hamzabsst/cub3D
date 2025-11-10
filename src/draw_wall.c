/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:31:07 by hbousset          #+#    #+#             */
/*   Updated: 2025/11/10 15:45:31 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	step = (double)hit.txtr->height / wall[2];
	tex_pos = (wall[0] - (WIN_HEIGHT - wall[2]) / 2) * step;
	y = wall[0];
	while (y <= wall[1])
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= hit.txtr->height)
			tex_y = hit.txtr->height - 1;
		color = *(int *)(hit.txtr->addr
				+ (tex_y * hit.txtr->line_len + wall[3] * (hit.txtr->bpp / 8)));
		*(int *)(game->buffer.addr + (y * game->buffer.line_len
					+ screen_x * (game->buffer.bpp / 8))) = color;
		tex_pos += step;
		y++;
	}
}

void	draw_wall(t_game *game, int screen_x, t_hit hit)
{
	int	wall_params[4];

	if (!hit.txtr || !hit.txtr->addr || hit.dis <= 0.001)
		return ;
	wall_params[2] = (int)(WIN_HEIGHT / hit.dis);
	wall_params[0] = (WIN_HEIGHT - wall_params[2]) / 2;
	wall_params[1] = wall_params[0] + wall_params[2];
	if (wall_params[0] < 0)
		wall_params[0] = 0;
	if (wall_params[1] >= WIN_HEIGHT)
		wall_params[1] = WIN_HEIGHT - 1;
	wall_params[3] = (int)(hit.hit_p * hit.txtr->width) % hit.txtr->width;
	wall_column(game, screen_x, hit, wall_params);
}
