/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:01:09 by abchaman          #+#    #+#             */
/*   Updated: 2025/09/24 04:20:35 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_error(char *msg)
{
	char	*full;

	full = ft_strjoin("Error: ", msg);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(full);
	return (1);
}

char	**dup_map(t_game *game)
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

static int	validate_filename(char *filename)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	if (!filename || !filename[0])
		return (1);
	while (filename[i])
	{
		if (filename[i] == '.' && filename[i + 1] == '.')
			return (1);
		if (filename[i] == '.')
			last = i;
		i++;
	}
	if (last <= 0)
		return (1);
	if (ft_strncmp(&filename[last], ".cub", 4))
		return (1);
	if (filename[last + 4] != '\0')
		return (1);
	return (0);
}

static int	count_file_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**load_file(char *filename)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;

	if (validate_filename(filename))
		return (ft_error("Invalid filename"), NULL);
	count = count_file_lines(filename);
	if (count <= 0)
		return (ft_error("Empty file or cannot read"), NULL);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(lines), ft_error("Cannot open file"), NULL);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines[count++] = line;
		line = get_next_line(fd);
	}
	return (lines[count] = NULL, close(fd), lines);
}
