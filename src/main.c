/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/08 18:16:08 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_texture(t_game *game, t_hit *result, t_ray *data, int side)
{
	char	cell;

	cell = '1';
	if (data->map_y >= 0 && data->map_y < game->map_height
		&& data->map_x >= 0 && data->map_x < game->map_width
		&& game->map[data->map_y]
		&& data->map_x < (int)ft_strlen(game->map[data->map_y]))
		cell = game->map[data->map_y][data->map_x];
	if (cell == ' ')
		result->txtr = &game->no_texture;
	else if (side == 0)
	{
		if (data->step_x > 0)
			result->txtr = &game->ea_texture;
		else
			result->txtr = &game->we_texture;
	}
	else
	{
		if (data->step_y > 0)
			result->txtr = &game->so_texture;
		else
			result->txtr = &game->no_texture;
	}
}

int	main(int ac, char **av)
{
	t_game	game;
	char	**lines;

	if (ac != 2)
		return (ft_error("invalid number of args"));
	lines = load_file(av[1]);
	if (!lines)
		return (1);
	init_var(&game);
	if (parse_file(lines, &game))
		return (ft_free(lines), 1);
	ft_free(lines);
	if (init_game(&game))
		return (cleanup(&game), 1);
	setup_colors(&game);
	if (render_buffer(&game))
		return (cleanup(&game), 1);
	run_game(&game);
	cleanup(&game);
	return (0);
}
