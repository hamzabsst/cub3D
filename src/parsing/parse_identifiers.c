/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:58:00 by hamza             #+#    #+#             */
/*   Updated: 2025/09/01 15:51:03 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	convert_rgb(char **rgb, int *color)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(rgb[i], " \t");
		if (!trimmed)
			return (1);
		color[i] = ft_atoi(trimmed);
		free(trimmed);
		if (color[i] < 0 || color[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

static int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		count;

	count = 0;
	while (*line == ' ')
		line++;
	if (*line != 'F' && *line != 'C')
		return (1);
	line++;
	while (*line == ' ')
		line++;
	if (!*line)
		return (1);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);
	while (rgb[count])
		count++;
	if (count != 3 || convert_rgb(rgb, color))
		return (ft_free(rgb), 1);
	ft_free(rgb);
	return (0);
}

static int	process_textures(char *trimmed, t_game *game)
{
	if (!ft_strncmp(trimmed, "NO ", 3))
	{
		if (!parse_texture(trimmed, &game->no_path))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "SO ", 3))
	{
		if (!parse_texture(trimmed, &game->so_path))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "WE ", 3))
	{
		if (!parse_texture(trimmed, &game->we_path))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "EA ", 3))
	{
		if (!parse_texture(trimmed, &game->ea_path))
			return (1);
	}
	return (0);
}

static int	process_colors(char *trimmed, t_game *game)
{
	if (!ft_strncmp(trimmed, "F ", 2))
	{
		if (!parse_color(trimmed, game->f_color))
			return (1);
	}
	else if (!ft_strncmp(trimmed, "C ", 2))
	{
		if (!parse_color(trimmed, game->c_color))
			return (1);
	}
	return (0);
}

int	process_identifier(char *trimmed, t_game *game)
{
	if (process_textures(trimmed, game))
		return (1);
	if (process_colors(trimmed, game))
		return (1);
	return (0);
}
