/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 17:54:21 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_direction(t_game *game, double x, double y, double plane_x)
{
	game->player.dir.x = x;
	game->player.dir.y = y;
	game->player.plane.x = plane_x;
	if (plane_x == 0)
		game->player.plane.y = 0.66;
	else
		game->player.plane.y = 0;
}

static int	init_player(t_game *game)
{
	if (game->player.start_dir == 'N')
		set_direction(game, 0, -1, 0.66);
	else if (game->player.start_dir == 'S')
		set_direction(game, 0, 1, -0.66);
	else if (game->player.start_dir == 'E')
		set_direction(game, 1, 0, 0);
	else if (game->player.start_dir == 'W')
		set_direction(game, -1, 0, 0);
	else
		return (ft_error("Invalid player start direction"));
	return (0);
}

static int	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		return (ft_error("Failed to initialize MiniLibX"));
	game->mlx.window = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx.window)
		return (ft_error("Failed to create window"));
	return (0);
}

static void	init_game(t_game *game)
{
	int	i;

	ft_bzero(game, sizeof(t_game));
	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!game->map)
		ft_error("Map alloc failed");
	game->player.x = -1;
	game->player.y = -1;
	game->player.start_dir = '\0';
	i = 0;
	while (i < 3)
	{
		game->floor_color[i] = -1;
		game->ceiling_color[i] = -1;
		i++;
	}
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
	init_game(&game);
	if (parse_file(lines, &game))
		return (ft_free(lines), ft_error("Parsing failed"));
	ft_free(lines);
	if (init_mlx(&game))
		return (cleanup_game(&game), 1);
	if (init_player(&game))
		return (cleanup_game(&game), 1);
	if (load_textures(&game))
		return (cleanup_game(&game), 1);
	setup_colors(&game);
	if (render_buffer(&game))
		return (cleanup_game(&game), 1);
	run_game(&game);
	cleanup_game(&game);
	return (0);
}
