/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 10:00:07 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_game(t_game *game)
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

static int	test_parsing(t_game *game)
{
	int	i;

	if (game->no_texture)
		ft_printf("NO: %s\n", game->no_texture);
	if (game->so_texture)
		ft_printf("SO: %s\n", game->so_texture);
	if (game->we_texture)
		ft_printf("WE: %s\n", game->we_texture);
	if (game->ea_texture)
		ft_printf("EA: %s\n", game->ea_texture);
	ft_printf("F: %d,%d,%d\nC: %d,%d,%d\n", game->floor_color[0],
		game->floor_color[1], game->floor_color[2],
		game->ceiling_color[0], game->ceiling_color[1],
		game->ceiling_color[2]);
	ft_printf("Map size: %dx%d\n",
		game->map->map_width, game->map->map_height);
	ft_printf("Player at (%.1f,%.1f) facing %c\n",
		game->player.x, game->player.y, game->player.start_dir);
	i = 0;
	while (i < game->map->map_height)
	{
		ft_printf("%s\n", game->map->map[i]);
		i++;
	}
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
	init_game(&game);
	if (parse_file(lines, &game))
		return (ft_free(lines), ft_error("Parsing failed"));
	test_parsing(&game);
	ft_free(lines);
	return (0);
}
