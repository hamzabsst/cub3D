/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:11:53 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/10 16:12:10 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	count_map_lines(char **lines, int start, int *count, int *max_w)
{
	int		i;
	int		j;
	char	*trimmed;

	i = start;
	*count = 0;
	*max_w = 0;
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], "\n");
		if (!trimmed || trimmed[0] == '\0')
		{
			if (*count > 0)
				return (free(trimmed), ft_error("Empty line in map"));
			free(trimmed);
			i++;
			continue;
		}
		j = 0;
		while (trimmed[j])
		{
			if (trimmed[j] == '\t')
				trimmed[j] = ' ';
			j++;
		}
		if ((int)ft_strlen(trimmed) > *max_w)
			*max_w = ft_strlen(trimmed);
		(*count)++;
		free(trimmed);
		i++;
	}
	if (*count == 0)
		return (ft_error("No map found"));
	return (0);
}

static int	copy_map_lines(char **lines, int start, t_game *game)
{
	int		i;
	int		j;
	int		k;
	char	*trimmed;

	i = start;
	j = 0;
	while (lines[i] && j < game->map->map_height)
	{
		trimmed = ft_strtrim(lines[i], "\n");
		if (trimmed && trimmed[0] != '\0')
		{
			k = 0;
			while (trimmed[k])
			{
				if (trimmed[k] == '\t')
					trimmed[k] = ' ';
				k++;
			}
			game->map->map[j] = malloc(game->map->map_width + 1);
			if (!game->map->map[j])
				return (free(trimmed), ft_error("Line allocation failed"));
			ft_strcpy(game->map->map[j], trimmed);
			k = ft_strlen(trimmed);
			while (k < game->map->map_width)
			{
				game->map->map[j][k] = ' ';
				k++;
			}
			game->map->map[j][game->map->map_width] = '\0';
			j++;
		}
		free(trimmed);
		i++;
	}
	game->map->map[game->map->map_height] = NULL;
	return (0);
}

int	extract_map(char **lines, int start, t_game *game)
{
	int	count;
	int	max_width;

	if (count_map_lines(lines, start, &count, &max_width))
		return (1);
	game->map->map_height = count;
	game->map->map_width = max_width;
	game->map->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map->map)
		return (ft_error("Map allocation failed"));
	if (copy_map_lines(lines, start, game))
		return (1);
	return (0);
}
