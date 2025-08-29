/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:58:00 by hamza             #+#    #+#             */
/*   Updated: 2025/08/23 09:51:17 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		return (1);
	if (parse_map(lines, game))
		return (1);
	return (0);
}
