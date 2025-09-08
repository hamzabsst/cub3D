/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:34 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/08 18:00:06 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	boss_collision(t_game *game)
{
	double	dx;
	double	dy;
	double	distance;
	double	current_time;

	if (!game->boss.active || game->hp <= 0)
		return ;
	dx = game->player_x - game->boss.x;
	dy = game->player_y - game->boss.y;
	distance = sqrt(dx * dx + dy * dy);
	current_time = get_current_time();
	if (distance < 0.8 && (current_time - game->last_dmg_time) > 1.0)
	{
		game->hp--;
		game->last_dmg_time = current_time;
		ft_printf("Boss hit you! Health remaining: %d\n", game->hp);
		if (game->hp <= 0)
		{
			ft_printf("Game Over! The boss has defeated you!\n");
			exit(0);
		}
	}
}

void	render_boss(t_game *game)
{
	t_point	screen_data;

	if (calculate_boss_screen_pos(game, &screen_data))
		draw_boss_sprite(game, screen_data);
}

int	init_boss(t_game *game)
{
	find_boss_position(game);
	game->boss.speed = 0.01;
	game->boss.frame = 0;
	game->boss.counter = 0;
	game->boss.delay = 8;
	game->boss.active = 1;
	game->boss.last_hit = 0;
	game->hp = 2;
	game->last_dmg_time = 0;
	if (load_boss_frames(game))
		return (1);
	ft_printf("Player health: %d\n", game->hp);
	return (0);
}

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
