/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/10 17:51:30 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	door_closed(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width
		|| !game->map[y] || x >= (int)ft_strlen(game->map[y]))
		return (0);
	return (game->map[y][x] == 'D');
}

static int	is_door_at(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height
		&& game->map[y] && x < (int)ft_strlen(game->map[y]))
	{
		if (game->map[y][x] == 'D' || game->map[y][x] == 'd')
			return (1);
	}
	return (0);
}

static int	find_door(t_game *game, int *door_x, int *door_y)
{
	double	px;
	double	py;
	double	dx;
	double	dy;

	px = (int)game->player_x;
	py = (int)game->player_y;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dx == 0 && dy == 0) && is_door_at(game, px + dx, py + dy))
			{
				*door_x = px + dx;
				*door_y = py + dy;
				return (1);
			}
			dx += 0.5;
		}
		dy += 0.5;
	}
	return (0);
}

static void	close_door(t_game *game, int door_x, int door_y)
{
	int	py;
	int	px;

	py = (int)game->player_y;
	px = (int)game->player_x;
	if (py >= 0 && py < game->map_height
		&& px >= 0 && px < game->map_width
		&& game->map[py] && px < (int)ft_strlen(game->map[py]))
	{
		if (game->map[door_y][door_x] != game->map[py][px])
			game->map[door_y][door_x] = 'D';
	}
	else
		game->map[door_y][door_x] = 'D';
}

void	toggle_door(t_game *game)
{
	int	door_x;
	int	door_y;

	if (find_door(game, &door_x, &door_y))
	{
		if (door_y >= 0 && door_y < game->map_height
			&& door_x >= 0 && door_x < game->map_width
			&& game->map[door_y]
			&& door_x < (int)ft_strlen(game->map[door_y]))
		{
			if (game->map[door_y][door_x] == 'D')
				game->map[door_y][door_x] = 'd';
			else if (game->map[door_y][door_x] == 'd')
				close_door(game, door_x, door_y);
		}
	}
}
