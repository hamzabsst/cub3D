/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 09:43:19 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	handle_keypress(int keycode, t_game *game)
{
	manage_player(keycode, game);
	if (keycode == ESC)
	{
		cleanup(game);
		exit(0);
	}
	return (0);
}

static int	game_loop(t_game *game)
{
	int		x;
	int		y;
	char	*row_addr;
	int		*pixel;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		row_addr = game->buffer.addr + (y * game->buffer.line_len);
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel = (int *)(row_addr + x * (game->buffer.bpp / 8));
			if (y < WIN_HEIGHT / 2)
				*pixel = game->c_rgb;
			else
				*pixel = game->f_rgb;
			x++;
		}
		y++;
	}
	(raycast(game), draw_minimap(game));
	mlx_put_image_to_window(game->mlx, game->window,
		game->buffer.img, 0, 0);
	return (0);
}

int	run_game(t_game *game)
{
	mlx_hook(game->window, 2, 1L, handle_keypress, game);
	mlx_hook(game->window, 6, 1L << 6, handle_mouse_motion, game);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}

void	cleanup(t_game *game)
{
	if (game->no_texture.img)
		mlx_destroy_image(game->mlx, game->no_texture.img);
	if (game->so_texture.img)
		mlx_destroy_image(game->mlx, game->so_texture.img);
	if (game->we_texture.img)
		mlx_destroy_image(game->mlx, game->we_texture.img);
	if (game->ea_texture.img)
		mlx_destroy_image(game->mlx, game->ea_texture.img);
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
	if (game->door_texture.img)
		mlx_destroy_image(game->mlx, game->door_texture.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		(mlx_destroy_display(game->mlx), free(game->mlx));
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->we_path)
		free(game->we_path);
	if (game->ea_path)
		free(game->ea_path);
	if (game->map)
		ft_free(game->map);
}
