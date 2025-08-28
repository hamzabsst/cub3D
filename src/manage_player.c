/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:32:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/28 11:03:07 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	rotate_player(int keycode, t_game *game, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == LEFT)
	{
		old_dir_x = game->dir_x;
		game->dir_x = old_dir_x * cos(speed) - game->dir_y * sin(speed);
		game->dir_y = old_dir_x * sin(speed) + game->dir_y * cos(speed);
		old_plane_x = game->plane_x;
		game->plane_x = old_plane_x * cos(speed) - game->plane_y * sin(speed);
		game->plane_y = old_plane_x * sin(speed) + game->plane_y * cos(speed);
	}
	if (keycode == RIGHT)
	{
		old_dir_x = game->dir_x;
		game->dir_x = old_dir_x * cos(-speed) - game->dir_y * sin(-speed);
		game->dir_y = old_dir_x * sin(-speed) + game->dir_y * cos(-speed);
		old_plane_x = game->plane_x;
		game->plane_x = old_plane_x * cos(-speed) - game->plane_y * sin(-speed);
		game->plane_y = old_plane_x * sin(-speed) + game->plane_y * cos(-speed);
	}
}

static void	move_up_down(int keycode, t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	if (keycode == W)
	{
		new_x = game->player_x + game->dir_x * speed;
		new_y = game->player_y + game->dir_y * speed;
		if (game->map[(int)new_y][(int)new_x] != '1'
			&& game->map[(int)new_y][(int)new_x] != ' ')
		{
			game->player_x = new_x;
			game->player_y = new_y;
		}
	}
	if (keycode == S)
	{
		new_x = game->player_x - game->dir_x * speed;
		new_y = game->player_y - game->dir_y * speed;
		if (game->map[(int)new_y][(int)new_x] != '1'
			&& game->map[(int)new_y][(int)new_x] != ' ')
		{
			game->player_x = new_x;
			game->player_y = new_y;
		}
	}
}

static void	move_right_left(int keycode, t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	if (keycode == A)
	{
		new_x = game->player_x - game->plane_x * speed;
		new_y = game->player_y - game->plane_y * speed;
		if (game->map[(int)new_y][(int)new_x] != '1'
			&& game->map[(int)new_y][(int)new_x] != ' ')
		{
			game->player_x = new_x;
			game->player_y = new_y;
		}
	}
	if (keycode == D)
	{
		new_x = game->player_x + game->plane_x * speed;
		new_y = game->player_y + game->plane_y * speed;
		if (game->map[(int)new_y][(int)new_x] != '1'
			&& game->map[(int)new_y][(int)new_x] != ' ')
		{
			game->player_x = new_x;
			game->player_y = new_y;
		}
	}
}

void	manage_player(int keycode, t_game *game)
{
	double	rot_speed;
	double	move_speed;

	rot_speed = 0.08;
	move_speed = 0.15;
	move_right_left(keycode, game, move_speed);
	move_up_down(keycode, game, move_speed);
	rotate_player(keycode, game, rot_speed);
}
