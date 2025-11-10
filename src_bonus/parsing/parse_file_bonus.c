/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:01:09 by abchaman          #+#    #+#             */
/*   Updated: 2025/11/10 22:37:44 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	parse_texture(char *line, char **texture_path)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	i = 0;
	while (split[i])
		i++;
	if (i < 2)
		return (ft_free(split), 1);
	if (*texture_path != NULL)
		return (ft_free(split), 1);
	*texture_path = ft_strdup(split[1]);
	ft_free(split);
	if (*texture_path)
		return (0);
	else
		return (1);
}

static int	parse_identifiers(char **lines, t_game *game)
{
	int		i;
	int		found;
	char	*trimmed;

	i = 0;
	found = 0;
	while (lines[i] && found < 6)
	{
		trimmed = ft_strtrim(lines[i], " \t\n");
		if (!trimmed || trimmed[0] == '\0')
		{
			free(trimmed);
			i++;
			continue ;
		}
		if (process_identifier(trimmed, game))
			found++;
		free(trimmed);
		i++;
	}
	if (found == 6)
		return (0);
	else
		return (1);
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

int	flood_fill(t_game *game, char **temp_map, int x, int y)
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

int	parse_file(char **lines, t_game *game)
{
	if (parse_identifiers(lines, game))
		return (ft_error("invalid identifiers"));
	if (parse_map(lines, game))
		return (1);
	return (0);
}
