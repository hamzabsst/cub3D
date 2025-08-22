/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:58:00 by hamza             #+#    #+#             */
/*   Updated: 2025/08/22 17:16:56 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_texture(char *line, char **texture_path)
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

static int	parse_color(char *line, int *color)
{
	char	*color_part;
	char	**rgb;
	char	*trimmed;
	int		i;
	int		count;

	color_part = ft_strchr(line, ' ');
	if (!color_part)
		return (1);
	color_part++;
	rgb = ft_split(color_part, ',');
	if (!rgb)
		return (1);
	count = 0;
	while (rgb[count])
		count++;
	if (count != 3)
		return (ft_free(rgb), 1);
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(rgb[i], " \t");
		if (!trimmed)
			return (ft_free(rgb), 1);
		color[i] = ft_atoi(trimmed);
		free(trimmed);
		if (color[i] < 0 || color[i] > 255)
			return (ft_free(rgb), 1);
		i++;
	}
	ft_free(rgb);
	return (0);
}

static int	process_identifier(char *trimmed, t_game *game)
{
	if (!ft_strncmp(trimmed, "NO ", 3))
	{
		if (!parse_texture(trimmed, &game->no_texture))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "SO ", 3))
	{
		if (!parse_texture(trimmed, &game->so_texture))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "WE ", 3))
	{
		if (!parse_texture(trimmed, &game->we_texture))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "EA ", 3))
	{
		if (!parse_texture(trimmed, &game->ea_texture))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "F ", 2))
	{
		if (!parse_color(trimmed, game->floor_color))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "C ", 2))
	{
		if (!parse_color(trimmed, game->ceiling_color))
			return (1);
	}
	return (0);
}

int	parse_identifiers(char **lines, t_game *game)
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
			continue;
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
