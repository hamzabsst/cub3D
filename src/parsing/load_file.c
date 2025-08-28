/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:01:09 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/28 10:27:46 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(char *msg)
{
	char	*full;

	full = ft_strjoin("Error: ", msg);
	ft_putstr_fd(full, 2);
	ft_putstr_fd("\n", 2);
	free(full);
	return (1);
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
		return (ft_error("invalid filename"), NULL);
	count = count_file_lines(filename);
	if (count <= 0)
		return (ft_error("empty file or cannot read"), NULL);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(lines), ft_error("cannot open file"), NULL);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines[count++] = line;
		line = get_next_line(fd);
	}
	return (lines[count] = NULL, close(fd), lines);
}
