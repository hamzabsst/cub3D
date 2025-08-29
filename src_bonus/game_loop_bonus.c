/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 11:45:52 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = old_dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = old_plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

static int	handle_mouse(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	double	rot_angle;

	(void)y;
	center_x = WIN_WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		rot_angle = delta_x * game->mouse_sens;
		rotate_player(game, rot_angle);
		mlx_mouse_move(game->mlx, game->window, center_x, WIN_HEIGHT / 2);
	}
	return (0);
}

int	run_game(t_game *game)
{
	mlx_hook(game->window, 2, 1L, handle_keypress, game);
	mlx_hook(game->window, 6, 1L << 6, handle_mouse, game);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
