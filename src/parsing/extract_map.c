/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:11:53 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 18:17:17 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	process_line(char *line, int *count, int *max_w)
{
	char	*trimmed;
	int		j;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed || trimmed[0] == '\0')
	{
		if (*count > 0)
			return (free(trimmed), ft_error("Empty line in map"));
		free(trimmed);
		return (0);
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
	return (0);
}

static int	count_lines(char **lines, int start, int *count, int *max_w)
{
	int		i;

	i = start;
	*count = 0;
	*max_w = 0;
	while (lines[i])
	{
		if (process_line(lines[i], count, max_w))
			return (1);
		i++;
	}
	if (*count == 0)
		return (ft_error("No map found"));
	return (0);
}

static int	process_and_copy_line(char *trimmed, t_game *game, int j)
{
	int		k;

	k = 0;
	while (trimmed[k])
	{
		if (trimmed[k] == '\t')
			trimmed[k] = ' ';
		k++;
	}
	game->map[j] = malloc(game->map_width + 1);
	if (!game->map[j])
		return (1);
	ft_strcpy(game->map[j], trimmed);
	k = ft_strlen(trimmed);
	while (k < game->map_width)
	{
		game->map[j][k] = ' ';
		k++;
	}
	game->map[j][game->map_width] = '\0';
	return (0);
}

static int	copy_lines(char **lines, int start, t_game *game)
{
	int		i;
	int		j;
	char	*trimmed;

	i = start;
	j = 0;
	while (lines[i] && j < game->map_height)
	{
		trimmed = ft_strtrim(lines[i], "\n");
		if (trimmed && trimmed[0] != '\0')
		{
			if (process_and_copy_line(trimmed, game, j))
				return (free(trimmed), ft_error("Line allocation failed"));
			j++;
		}
		free(trimmed);
		i++;
	}
	game->map[game->map_height] = NULL;
	return (0);
}

int	extract_map(char **lines, int start, t_game *game)
{
	int	count;
	int	max_width;

	if (count_lines(lines, start, &count, &max_width))
		return (1);
	game->map_height = count;
	game->map_width = max_width;
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return (ft_error("Map allocation failed"));
	if (copy_lines(lines, start, game))
		return (1);
	return (0);
}
