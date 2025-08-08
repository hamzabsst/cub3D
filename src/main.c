/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/08 18:16:57 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	char	**lines;
	// t_var	game;
	if (ac == 2)
	{
		if (check_name(av[1]))
			return (printf("name of map invalid"), 1);
		lines = open_read(av[1]);
		if (!lines)
			return (1);
		// parse_file(lines);
		// game.mlx = mlx_init();
		// if (!game.mlx)
		// 	return (1);
		// game.ac = ac;
		// game.av = av;
		// game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");
		// if (!game.win)
		// 	return (1);
		// mlx_loop(game.mlx);
		// return (0);
	}
}

