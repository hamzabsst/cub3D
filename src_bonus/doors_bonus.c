/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 11:44:33 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_door_at(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
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

void	toggle_door(t_game *game)
{
	int	door_x;
	int	door_y;

	if (find_door(game, &door_x, &door_y))
	{
		if (game->map[door_y][door_x] == 'D')
			game->map[door_y][door_x] = 'd';
		else if (game->map[door_y][door_x] == 'd'
			&& game->map[door_y][door_x]
			!= game->map[(int)game->player_y][(int)game->player_x])
			game->map[door_y][door_x] = 'D';
	}
}

int	door_closed(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (0);
	return (game->map[y][x] == 'D');
}
