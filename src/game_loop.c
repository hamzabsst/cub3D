/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 12:44:58 by hbousset         ###   ########.fr       */
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

static int	game_loop(t_game *game)
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
			*(int *)(game->buffer.addr + (y * game->buffer.line_length
						+ x * (game->buffer.bits_per_pixel / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->window,
		game->buffer.img, 0, 0);
	return (0);
}

int	run_game(t_game *game)
{
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}

void	cleanup_game(t_game *game)
{
	if (game->north_texture.img)
		mlx_destroy_image(game->mlx, game->north_texture.img);
	if (game->south_texture.img)
		mlx_destroy_image(game->mlx, game->south_texture.img);
	if (game->west_texture.img)
		mlx_destroy_image(game->mlx, game->west_texture.img);
	if (game->east_texture.img)
		mlx_destroy_image(game->mlx, game->east_texture.img);
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->no_texture_path)
		free(game->no_texture_path);
	if (game->so_texture_path)
		free(game->so_texture_path);
	if (game->we_texture_path)
		free(game->we_texture_path);
	if (game->ea_texture_path)
		free(game->ea_texture_path);
	if (game->map)
		ft_free(game->map);
}
