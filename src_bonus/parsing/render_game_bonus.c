/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:22:15 by abchaman          #+#    #+#             */
/*   Updated: 2025/09/24 04:21:24 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	setup_colors(t_game *game)
{
	game->f_rgb = (game->f_color[0] << 16)
		| (game->f_color[1] << 8) | game->f_color[2];
	game->c_rgb = (game->c_color[0] << 16)
		| (game->c_color[1] << 8) | game->c_color[2];
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
