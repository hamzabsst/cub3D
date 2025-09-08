/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:32:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/08 13:16:23 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_pos_blocked(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (1);
	if (!game->map[map_y])
		return (1);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (1);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (1);
	if (game->map[map_y][map_x] == 'D' && door_closed(game, map_x, map_y))
		return (1);
	return (0);
}

static int	can_move(t_game *game, double new_x, double new_y)
{
	double	buffer;
	int		map_x;
	int		map_y;

	buffer = 0.15;
	map_x = (int)(new_x + buffer);
	map_y = (int)(new_y + buffer);
	if (is_pos_blocked(game, map_x, map_y))
		return (0);
	map_x = (int)(new_x - buffer);
	map_y = (int)(new_y - buffer);
	if (is_pos_blocked(game, map_x, map_y))
		return (0);
	map_x = (int)(new_x + buffer);
	map_y = (int)(new_y - buffer);
	if (is_pos_blocked(game, map_x, map_y))
		return (0);
	map_x = (int)(new_x - buffer);
	map_y = (int)(new_y + buffer);
	if (is_pos_blocked(game, map_x, map_y))
		return (0);
	return (1);
}

static void	move_up_down(int keycode, t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	if (keycode == W)
	{
		new_x = game->player_x + game->dir_x * speed;
		new_y = game->player_y + game->dir_y * speed;
		if (can_move(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move(game, game->player_x, new_y))
			game->player_y = new_y;
	}
	if (keycode == S)
	{
		new_x = game->player_x - game->dir_x * speed;
		new_y = game->player_y - game->dir_y * speed;
		if (can_move(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move(game, game->player_x, new_y))
			game->player_y = new_y;
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
		if (can_move(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move(game, game->player_x, new_y))
			game->player_y = new_y;
	}
	if (keycode == D)
	{
		new_x = game->player_x + game->plane_x * speed;
		new_y = game->player_y + game->plane_y * speed;
		if (can_move(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move(game, game->player_x, new_y))
			game->player_y = new_y;
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	double	move_speed;

	move_speed = 0.15;
	move_right_left(keycode, game, move_speed);
	move_up_down(keycode, game, move_speed);
	if (keycode == E)
		toggle_door(game);
	if (keycode == ESC)
		(cleanup(game), exit(0));
	return (0);
}
