/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:29:05 by abchaman          #+#    #+#             */
/*   Updated: 2025/11/10 22:36:35 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		if (!game->map[i])
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < game->map_width && j < (int)ft_strlen(game->map[i]))
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

static int	is_valid_neighbor(t_game *game, char **temp_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (1);
	if (y >= game->map_height || x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (temp_map[y][x] == ' ')
		return (1);
	return (0);
}

static int	flood_fill(t_game *game, char **temp_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width
		|| y >= game->map_height)
		return (1);
	if (y >= game->map_height || x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'V')
		return (0);
	if (temp_map[y][x] == ' ')
		return (1);
	temp_map[y][x] = 'V';
	if (is_valid_neighbor(game, temp_map, x + 1, y)
		|| is_valid_neighbor(game, temp_map, x - 1, y)
		|| is_valid_neighbor(game, temp_map, x, y + 1)
		|| is_valid_neighbor(game, temp_map, x, y - 1))
		return (1);
	if (flood_fill(game, temp_map, x + 1, y)
		|| flood_fill(game, temp_map, x - 1, y)
		|| flood_fill(game, temp_map, x, y + 1)
		|| flood_fill(game, temp_map, x, y - 1))
		return (1);
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
	int		result;

	if (check_walls(game))
		return (1);
	temp_map = dup_map(game);
	if (!temp_map)
		return (ft_error("Memory allocation failed"));
	result = flood_fill(game, temp_map, (int)game->player_x,
			(int)game->player_y);
	ft_free(temp_map);
	if (result)
		return (ft_error("Map not closed walkable area touches space"));
	return (0);
}
