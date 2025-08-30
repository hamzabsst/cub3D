/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/30 10:13:43 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	setup_colors(t_game *game)
{
	game->f_rgb = (game->f_color[0] << 16)
		| (game->f_color[1] << 8) | game->f_color[2];
	game->c_rgb = (game->c_color[0] << 16)
		| (game->c_color[1] << 8) | game->c_color[2];
}

int	main(int ac, char **av)
{
	char	**lines;
	t_game	game;

	if (ac != 2)
		return (ft_error("Usage: ./cub3D map.cub"));
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
	if (init_boss(&game))
		return (cleanup(&game), 1);
	if (render_buffer(&game))
		return (cleanup(&game), 1);
	run_game(&game);
	cleanup(&game);
	return (0);
}
