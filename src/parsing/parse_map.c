/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:11:23 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 09:59:00 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	process_player(t_game *game, char c, int coords, int *players)
{
	int	i;
	int	j;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*players > 0)
			return (ft_error("Multiple players found"));
		(*players)++;
		i = coords / 1000;
		j = coords % 1000;
		game->player_x = j + 0.5;
		game->player_y = i + 0.5;
		game->start_dir = c;
		game->map[i][j] = '0';
	}
	return (0);
}

static int	validate_player(t_game *game)
{
	int		i;
	int		j;
	int		players;
	char	c;

	players = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ')
				return (ft_error("Invalid character in map"));
			if (process_player(game, c, i * 1000 + j, &players))
				return (1);
			j++;
		}
		i++;
	}
	if (players == 0)
		return (ft_error("No player found"));
	return (0);
}

static int	find_map_start(char **lines)
{
	int		i;
	int		found;
	char	*trim;

	i = -1;
	found = 0;
	while (lines[++i] && found < 6)
	{
		trim = ft_strtrim(lines[i], " \t\n");
		if (trim && trim[0] != '\0'
			&& (!ft_strncmp(trim, "NO ", 3) || !ft_strncmp(trim, "SO ", 3)
				|| !ft_strncmp(trim, "WE ", 3) || !ft_strncmp(trim, "EA ", 3)
				|| !ft_strncmp(trim, "F ", 2) || !ft_strncmp(trim, "C ", 2)))
			found++;
		free(trim);
	}
	while (lines[i])
	{
		trim = ft_strtrim(lines[i], " \t\n");
		if (trim && trim[0] != '\0')
			return (free(trim), i);
		free(trim);
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
	if (validate_player(game))
		return (1);
	if (validate_wall(game))
		return (1);
	return (0);
}
