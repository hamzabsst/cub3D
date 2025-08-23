/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 11:41:34 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_texture_image(t_game *game, t_image *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (1);
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_texture_image(game, &game->textures.north, game->no_texture))
		return (ft_error("Failed to load north texture"));
	if (load_texture_image(game, &game->textures.south, game->so_texture))
		return (ft_error("Failed to load south texture"));
	if (load_texture_image(game, &game->textures.west, game->we_texture))
		return (ft_error("Failed to load west texture"));
	if (load_texture_image(game, &game->textures.east, game->ea_texture))
		return (ft_error("Failed to load east texture"));
	return (0);
}

void	setup_colors(t_game *game)
{
	game->floor_rgb = (game->floor_color[0] << 16)
		| (game->floor_color[1] << 8) | game->floor_color[2];
	game->ceiling_rgb = (game->ceiling_color[0] << 16)
		| (game->ceiling_color[1] << 8) | game->ceiling_color[2];
	// ft_printf("%d", game->ceiling_rgb);
}

int	render_buffer(t_game *game)
{
	game->mlx.buffer.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	if (!game->mlx.buffer.img)
		return (ft_error("Failed to create render buffer"));
	game->mlx.buffer.addr = mlx_get_data_addr(game->mlx.buffer.img,
			&game->mlx.buffer.bits_per_pixel,
			&game->mlx.buffer.line_length,
			&game->mlx.buffer.endian);
	if (!game->mlx.buffer.addr)
		return (ft_error("Failed to get buffer address"));
	game->mlx.buffer.width = WIDTH;
	game->mlx.buffer.height = HEIGHT;
	return (0);
}
