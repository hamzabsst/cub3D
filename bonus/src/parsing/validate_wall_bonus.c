/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_wall_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:29:05 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/25 10:53:00 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	check_border_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1
					|| j == 0 || j == game->map_width - 1)
				&& (game->map[i][j] == '0'))
				return (ft_error("Map not closed - walkable area at border"));
			j++;
		}
		i++;
	}
	return (0);
}

static int	flood_fill(t_game *game, char **temp_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width
		|| y >= game->map_height)
		return (0);
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'V')
		return (0);
	if (temp_map[y][x] == ' ')
	{
		temp_map[y][x] = 'V';
		flood_fill(game, temp_map, x + 1, y);
		flood_fill(game, temp_map, x - 1, y);
		flood_fill(game, temp_map, x, y + 1);
		flood_fill(game, temp_map, x, y - 1);
		return (0);
	}
	temp_map[y][x] = 'V';
	flood_fill(game, temp_map, x + 1, y);
	flood_fill(game, temp_map, x - 1, y);
	flood_fill(game, temp_map, x, y + 1);
	flood_fill(game, temp_map, x, y - 1);
	return (0);
}

static char	**dup_map(t_game *game)
{
	char	**temp_map;
	int		i;
	int		j;

	temp_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		temp_map[i] = malloc(game->map_width + 1);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			return (free(temp_map), NULL);
		}
		j = -1;
		while (++j < game->map_width)
			temp_map[i][j] = game->map[i][j];
		temp_map[i][j] = '\0';
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

int	validate_wall(t_game *game)
{
	char	**temp_map;

	if (check_border_walls(game))
		return (1);
	temp_map = dup_map(game);
	if (!temp_map)
		return (ft_error("Memory allocation failed"));
	flood_fill(game, temp_map, (int)game->player_x, (int)game->player_y);
	ft_free(temp_map);
	return (0);
}
