/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:58:00 by hamza             #+#    #+#             */
/*   Updated: 2025/08/10 16:18:16 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_file(char **lines, t_game *game)
{
	if (parse_identifiers(lines, game))
		return (1);
	if (parse_map(lines, game))
		return (1);
	return (0);
}
