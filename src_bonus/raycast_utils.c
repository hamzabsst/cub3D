/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:08:26 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/08 18:13:03 by hbousset         ###   ########.fr       */
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

static void	set_wall_texture(t_game *game, t_hit *result, t_ray *data, int side)
{
	if (side == 0)
	{
		if (data->step_x > 0)
			result->txtr = &game->ea_texture;
		else
			result->txtr = &game->we_texture;
	}
	else
	{
		if (data->step_y > 0)
			result->txtr = &game->so_texture;
		else
			result->txtr = &game->no_texture;
	}
}

void	set_texture(t_game *game, t_hit *result, t_ray *data, int side)
{
	char	cell;

	cell = '1';
	if (data->map_y >= 0 && data->map_y < game->map_height
		&& data->map_x >= 0 && data->map_x < game->map_width
		&& game->map[data->map_y]
		&& data->map_x < (int)ft_strlen(game->map[data->map_y]))
	{
		cell = game->map[data->map_y][data->map_x];
	}
	if (cell == 'D')
		result->txtr = &game->door_texture;
	else if (cell == ' ')
		result->txtr = &game->no_texture;
	else
		set_wall_texture(game, result, data, side);
}
