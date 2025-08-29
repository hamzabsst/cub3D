/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:32:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 10:03:04 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

int	handle_mouse(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	double	rotation_angle;

	(void)y;
	center_x = WIN_WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		rotation_angle = delta_x * game->mouse_sens;
		rotate_player(game, rotation_angle);
		mlx_mouse_move(game->mlx, game->window, center_x, WIN_HEIGHT / 2);
	}
	return (0);
}

static int	can_move_to(t_game *game, double new_x, double new_y)
{
	double	buffer;
	int		map_x;
	int		map_y;

	buffer = 0.15;
	map_x = (int)(new_x + buffer);
	map_y = (int)(new_y + buffer);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (0);
	if (game->map[map_y][map_x] == 'D' && door_closed(game, map_x, map_y))
		return (0);
	map_x = (int)(new_x - buffer);
	map_y = (int)(new_y - buffer);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (0);
	if (game->map[map_y][map_x] == 'D' && door_closed(game, map_x, map_y))
		return (0);
	map_x = (int)(new_x + buffer);
	map_y = (int)(new_y - buffer);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (0);
	if (game->map[map_y][map_x] == 'D' && door_closed(game, map_x, map_y))
		return (0);
	map_x = (int)(new_x - buffer);
	map_y = (int)(new_y + buffer);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (0);
	if (game->map[map_y][map_x] == 'D' && door_closed(game, map_x, map_y))
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
		if (can_move_to(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move_to(game, game->player_x, new_y))
			game->player_y = new_y;
	}
	if (keycode == S)
	{
		new_x = game->player_x - game->dir_x * speed;
		new_y = game->player_y - game->dir_y * speed;
		if (can_move_to(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move_to(game, game->player_x, new_y))
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
		if (can_move_to(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move_to(game, game->player_x, new_y))
			game->player_y = new_y;
	}
	if (keycode == D)
	{
		new_x = game->player_x + game->plane_x * speed;
		new_y = game->player_y + game->plane_y * speed;
		if (can_move_to(game, new_x, game->player_y))
			game->player_x = new_x;
		if (can_move_to(game, game->player_x, new_y))
			game->player_y = new_y;
	}
}

void	manage_player(int keycode, t_game *game)
{
	double	move_speed;

	move_speed = 0.15;
	move_right_left(keycode, game, move_speed);
	move_up_down(keycode, game, move_speed);
	if (keycode == E)
		toggle_door(game);
}
