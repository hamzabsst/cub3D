/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 11:51:26 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

static int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	return (0);
}

static void	render_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				color = game->ceiling_rgb;
			else
				color = game->floor_rgb;
			*(int *)(game->mlx.buffer.addr + (y * game->mlx.buffer.line_length
						+ x * (game->mlx.buffer.bits_per_pixel / 8))) = color;
			x++;
		}
		y++;
	}
}

static int	game_loop(t_game *game)
{
	render_ceiling_and_floor(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window,
		game->mlx.buffer.img, 0, 0);
	return (0);
}

int	run_game(t_game *game)
{
	mlx_hook(game->mlx.window, 17, 0, close_window, game);
	mlx_hook(game->mlx.window, 2, 1L << 0, handle_keypress, game);
	mlx_loop_hook(game->mlx.mlx, game_loop, game);
	mlx_loop(game->mlx.mlx);
	return (0);
}

void	cleanup_game(t_game *game)
{
	if (game->textures.north.img)
		mlx_destroy_image(game->mlx.mlx, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->mlx.mlx, game->textures.south.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->mlx.mlx, game->textures.west.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->mlx.mlx, game->textures.east.img);
	if (game->mlx.buffer.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.buffer.img);
	if (game->mlx.window)
		mlx_destroy_window(game->mlx.mlx, game->mlx.window);
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
	if (game->map && game->map->map)
		ft_free(game->map->map);
	if (game->map)
		free(game->map);
}
