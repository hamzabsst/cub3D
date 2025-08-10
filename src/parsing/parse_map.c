/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:11:23 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/10 16:21:42 by hbousset         ###   ########.fr       */
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

static int	check_wall_adjacency(t_game *game, int i, int j, int first, int last)
{
	if ((i > 0 && j >= first && j <= last && game->map->map[i - 1][j] == ' ') ||
		(i < game->map->map_height - 1 && j >= first && j <= last &&
		game->map->map[i + 1][j] == ' ') ||
		(j > first && game->map->map[i][j - 1] == ' ') ||
		(j < last && game->map->map[i][j + 1] == ' '))
		return (ft_error("Map not closed - walkable area adjacent to void"));
	return (0);
}

static int	validate_wall_closure(t_game *game)
{
	int	i;
	int	j;
	int	first_nonspace;
	int	last_nonspace;

	i = 0;
	while (i < game->map->map_height)
	{
		j = 0;
		while (j < game->map->map_width)
		{
			if (game->map->map[i][j] == '0')
			{
				if (i == 0 || i == game->map->map_height - 1)
					return (ft_error("Map not closed - touches border"));
				first_nonspace = 0;
				last_nonspace = game->map->map_width - 1;
				while (first_nonspace < game->map->map_width &&
					game->map->map[i][first_nonspace] == ' ')
					first_nonspace++;
				while (last_nonspace >= 0 &&
					game->map->map[i][last_nonspace] == ' ')
					last_nonspace--;
				if (j < first_nonspace || j > last_nonspace)
					return (ft_error("Map not closed - in exterior space"));
				if (check_wall_adjacency(game, i, j, first_nonspace, last_nonspace))
					return (1);
			}
			j++;
		}
		i++;
	}
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
