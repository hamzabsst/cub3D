/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 12:45:07 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_texture_image(t_game *game, t_image *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
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
	if (load_texture_image(game, &game->north_texture, game->no_texture_path))
		return (ft_error("Failed to load north texture"));
	if (load_texture_image(game, &game->south_texture, game->so_texture_path))
		return (ft_error("Failed to load south texture"));
	if (load_texture_image(game, &game->west_texture, game->we_texture_path))
		return (ft_error("Failed to load west texture"));
	if (load_texture_image(game, &game->east_texture, game->ea_texture_path))
		return (ft_error("Failed to load east texture"));
	return (0);
}

void	setup_colors(t_game *game)
{
	game->floor_rgb = (game->floor_color[0] << 16)
		| (game->floor_color[1] << 8) | game->floor_color[2];
	game->ceiling_rgb = (game->ceiling_color[0] << 16)
		| (game->ceiling_color[1] << 8) | game->ceiling_color[2];
}

int	render_buffer(t_game *game)
{
	game->buffer.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->buffer.img)
		return (ft_error("Failed to create render buffer"));
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length,
			&game->buffer.endian);
	if (!game->buffer.addr)
		return (ft_error("Failed to get buffer address"));
	game->buffer.width = WIDTH;
	game->buffer.height = HEIGHT;
	return (0);
}
