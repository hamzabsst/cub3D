/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:11:23 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/22 14:04:06 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_chars_and_player(t_game *game)
{
	int		i;
	int		j;
	int		players;
	char	c;

	players = 0;
	i = 0;
	while (i < game->map->map_height)
	{
		j = 0;
		while (j < game->map->map_width)
		{
			c = game->map->map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' &&
				c != 'E' && c != 'W' && c != ' ')
				return (ft_error("Invalid character in map"));
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (players > 0)
					return (ft_error("Multiple players found"));
				players++;
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player.start_dir = c;
				game->map->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (players == 0)
		return (ft_error("No player found"));
	return (0);
}

static int	check_border_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->map_height)
	{
		j = 0;
		while (j < game->map->map_width)
		{
			if ((i == 0 || i == game->map->map_height - 1 ||
				j == 0 || j == game->map->map_width - 1) &&
				(game->map->map[i][j] == '0'))
				return (ft_error("Map not closed - walkable area at border"));
			j++;
		}
		i++;
	}
	return (0);
}

static int	flood_fill(t_game *game, char **temp_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map->map_width || y >= game->map->map_height)
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

	temp_map = malloc(sizeof(char *) * (game->map->map_height + 1));
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < game->map->map_height)
	{
		temp_map[i] = malloc(game->map->map_width + 1);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (NULL);
		}
		j = 0;
		while (j < game->map->map_width)
		{
			temp_map[i][j] = game->map->map[i][j];
			j++;
		}
		temp_map[i][j] = '\0';
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

static int	validate_wall_closure(t_game *game)
{
	char	**temp_map;

	if (check_border_walls(game))
		return (1);
	temp_map = dup_map(game);
	if (!temp_map)
		return (ft_error("Memory allocation failed"));
	flood_fill(game, temp_map, (int)game->player.x, (int)game->player.y);
	ft_free(temp_map);
	return (0);
}

static int	find_map_start(char **lines)
{
	int		i;
	int		found;
	char	*trimmed;

	i = 0;
	found = 0;
	while (lines[i] && found < 6)
	{
		trimmed = ft_strtrim(lines[i], " \t\n");
		if (trimmed && trimmed[0] != '\0' &&
			(!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3) ||
			!ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3) ||
			!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2)))
			found++;
		free(trimmed);
		i++;
	}
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], " \t\n");
		if (trimmed && trimmed[0] != '\0')
		{
			free(trimmed);
			return (i);
		}
		free(trimmed);
		i++;
	}
	return (-1);
}

int	parse_map(char **lines, t_game *game)
{
	int	map_start;

	map_start = find_map_start(lines);
	if (map_start < 0)
		return (ft_error("No map found after identifiers"));
	if (extract_map(lines, map_start, game))
		return (1);
	if (validate_chars_and_player(game))
		return (1);
	if (validate_wall_closure(game))
		return (1);
	return (0);
}
