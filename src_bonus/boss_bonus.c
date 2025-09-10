/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/10 17:34:19 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	calculate_boss_screen_pos(t_game *game, t_point *screen_data)
{
	double	dx;
	double	dy;
	double	angle;

	if (!game->boss.active)
		return (0);
	dx = game->boss.x - game->player_x;
	dy = game->boss.y - game->player_y;
	screen_data->dist = sqrt(dx * dx + dy * dy);
	if (screen_data->dist > 10.0)
		return (0);
	angle = atan2(dy, dx) - atan2(game->dir_y, game->dir_x);
	while (angle > PI)
		angle -= 2 * PI;
	while (angle < -PI)
		angle += 2 * PI;
	if (angle > PI / 3 || angle < -PI / 3)
		return (0);
	screen_data->x = (int)(WIN_WIDTH / 2 * (1 + angle / (PI / 3)));
	screen_data->size = (int)(WIN_HEIGHT / screen_data->dist * 1.5);
	return (1);
}

static void	boss_collision(t_game *game)
{
	double	dx;
	double	dy;
	double	distance;

	if (!game->boss.active || game->hp <= 0)
		return ;
	dx = game->player_x - game->boss.x;
	dy = game->player_y - game->boss.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 0.8 && game->last_dmg_time == 0)
	{
		game->hp--;
		game->last_dmg_time = 60;
		if (game->hp <= 0)
		{
			ft_printf("Game Over! The boss has defeated you!\n");
			exit(0);
		}
	}
	if (game->last_dmg_time > 0)
		game->last_dmg_time--;
}

static int	is_move_valid(t_game *game, double new_x, double new_y)
{
	int	check_x;
	int	check_y;

	check_x = (int)new_x;
	check_y = (int)new_y;
	if (check_y < 0 || check_y >= game->map_height
		|| check_x < 0 || check_x >= game->map_width
		|| !game->map[check_y] || check_x >= (int)ft_strlen(game->map[check_y]))
		return (0);
	if (game->map[check_y][check_x] == '1'
		|| game->map[check_y][check_x] == 'D')
		return (0);
	return (1);
}

static void	move_boss(t_game *game)
{
	double	dx;
	double	dy;
	double	distance;
	double	new_x;
	double	new_y;

	dx = game->player_x - game->boss.x;
	dy = game->player_y - game->boss.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 0.1)
		return ;
	dx /= distance;
	dy /= distance;
	new_x = game->boss.x + dx * game->boss.speed;
	new_y = game->boss.y + dy * game->boss.speed;
	if (is_move_valid(game, game->boss.x, new_y))
		game->boss.y = new_y;
	if (is_move_valid(game, new_x, game->boss.y))
		game->boss.x = new_x;
}

void	render_boss(t_game *game)
{
	t_point	screen_data;

	if (!game->boss.active)
		return ;
	game->boss.counter++;
	if (game->boss.counter >= game->boss.delay)
	{
		game->boss.frame = (game->boss.frame + 1) % 6;
		game->boss.counter = 0;
	}
	move_boss(game);
	boss_collision(game);
	if (calculate_boss_screen_pos(game, &screen_data))
		draw_boss_sprite(game, screen_data);
}
