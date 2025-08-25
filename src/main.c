/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/25 09:08:32 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	setup_colors(t_game *game)
{
	game->f_rgb = (game->f_color[0] << 16)
		| (game->f_color[1] << 8) | game->f_color[2];
	game->c_rgb = (game->c_color[0] << 16)
		| (game->c_color[1] << 8) | game->c_color[2];
}

static int	render_buffer(t_game *game)
{
	game->buffer.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->buffer.img)
		return (ft_error("Failed to create render buffer"));
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bpp,
			&game->buffer.line_len,
			&game->buffer.endian);
	if (!game->buffer.addr)
		return (ft_error("Failed to get buffer address"));
	game->buffer.width = WIN_WIDTH;
	game->buffer.height = WIN_HEIGHT;
	return (0);
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
	init_variables(&game);
	if (parse_file(lines, &game))
		return (ft_free(lines), ft_error("Parsing failed"));
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
