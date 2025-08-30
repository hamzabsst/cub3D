/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:58:00 by hamza             #+#    #+#             */
/*   Updated: 2025/08/30 11:44:44 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

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

int	parse_file(char **lines, t_game *game)
{
	if (parse_identifiers(lines, game))
		return (ft_error("invalid identifiers"));
	if (parse_map(lines, game))
		return (1);
	return (0);
}
