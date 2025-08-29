/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 10:03:04 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_door(t_game *game)
{
	int	y;
	int	x;

	game->door_states = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->door_states)
		return ;
	y = 0;
	while (y < game->map_height)
	{
		game->door_states[y] = malloc(sizeof(char) * (game->map_width + 1));
		if (!game->door_states[y])
			return ;
		x = 0;
		while (x < game->map_width && game->map[y][x])
		{
			if (game->map[y][x] == 'D')
				game->door_states[y][x] = '1';
			else
				game->door_states[y][x] = '0';
			x++;
		}
		while (x < game->map_width)
		{
			game->door_states[y][x] = '0';
			x++;
		}
		game->door_states[y][x] = '\0';
		y++;
	}
	game->door_states[y] = NULL;
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
			if (dx == 0 && dy == 0)
			{
				dx++;
				continue;
			}
			if (px + dx >= 0 && px + dx < game->map_width &&
				py + dy >= 0 && py + dy < game->map_height)
			{
				if (game->map[(int)(py + dy)][(int)(px + dx)] == 'D')
				{
					*door_x = px + dx;
					*door_y = py + dy;
					return (1);
				}
			}
			dx+= 0.5;
		}
		dy+= 0.5;
	}
	return (0);
}

void	toggle_door(t_game *game)
{
	int	door_x;
	int	door_y;

	if (!game->door_states)
		return ;
	if (find_door(game, &door_x, &door_y))
	{
		if (game->door_states[door_y][door_x] == '1')
			game->door_states[door_y][door_x] = '0';
		else
			game->door_states[door_y][door_x] = '1';
	}
}

int	door_open(t_game *game, int x, int y)
{
	if (!game->door_states || y < 0 || y >= game->map_height ||
		x < 0 || x >= game->map_width)
		return (0);
	if (game->map[y][x] == 'D')
		return (game->door_states[y][x] == '0');
	return (0);
}

int	door_closed(t_game *game, int x, int y)
{
	if (!game->door_states || y < 0 || y >= game->map_height ||
		x < 0 || x >= game->map_width)
		return (0);
	if (game->map[y][x] == 'D')
		return (game->door_states[y][x] == '1');
	return (0);
}
