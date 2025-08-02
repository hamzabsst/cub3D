/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/02 20:15:44 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_var	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.ac = ac;
	game.av = av;
	game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");
	if (!game.win)
		return (1);
	mlx_loop(game.mlx);
	return (0);
}

