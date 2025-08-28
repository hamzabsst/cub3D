/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/28 10:32:05 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	game;
	char	**lines;

	if (ac != 2)
		return (ft_error("invalid number of args"));
	lines = load_file(av[1]);
	if (!lines)
		return (1);
	init_variables(&game);
	if (parse_file(lines, &game))
		return (ft_free(lines), ft_error("parsing failed"));
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
