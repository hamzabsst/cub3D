/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:58:00 by hamza             #+#    #+#             */
/*   Updated: 2025/08/23 09:18:24 by hbousset         ###   ########.fr       */
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
	char	*color_part;
	char	**rgb;
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
	if (convert_rgb(rgb, color))
		return (ft_free(rgb), 1);
	ft_free(rgb);
	return (0);
}

static int	process_textures(char *trimmed, t_game *game)
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
	return (0);
}

static int	process_colors(char *trimmed, t_game *game)
{
	if (!ft_strncmp(trimmed, "F ", 2))
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

int	process_identifier(char *trimmed, t_game *game)
{
	if (process_textures(trimmed, game))
		return (1);
	if (process_colors(trimmed, game))
		return (1);
	return (0);
}
