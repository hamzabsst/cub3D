/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:00:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/08 13:16:23 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	move_boss_towards_player(t_game *game)
{
	double	dx;
	double	dy;
	double	distance;
	double	new_x;
	double	new_y;
	int		check_x, check_y;

	dx = game->player_x - game->boss.x;
	dy = game->player_y - game->boss.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 0.1)
		return ;
	dx /= distance;
	dy /= distance;
	new_x = game->boss.x + dx * game->boss.speed;
	new_y = game->boss.y + dy * game->boss.speed;

	check_y = (int)new_y;
	check_x = (int)game->boss.x;
	if (check_y >= 0 && check_y < game->map_height &&
		check_x >= 0 && check_x < game->map_width &&
		game->map[check_y] && check_x < (int)ft_strlen(game->map[check_y]) &&
		game->map[check_y][check_x] != '1')
		game->boss.y = new_y;

	check_y = (int)game->boss.y;
	check_x = (int)new_x;
	if (check_y >= 0 && check_y < game->map_height &&
		check_x >= 0 && check_x < game->map_width &&
		game->map[check_y] && check_x < (int)ft_strlen(game->map[check_y]) &&
		game->map[check_y][check_x] != '1')
		game->boss.x = new_x;
}

void	check_boss_collision(t_game *game)
{
	double	dx;
	double	dy;
	double	distance;
	double	current_time;

	if (!game->boss.active || game->player_health <= 0)
		return ;
	dx = game->player_x - game->boss.x;
	dy = game->player_y - game->boss.y;
	distance = sqrt(dx * dx + dy * dy);
	current_time = get_current_time();
	if (distance < 0.8 && (current_time - game->last_damage_time) > 1.0)
	{
		game->player_health--;
		game->last_damage_time = current_time;
		ft_printf("Boss hit you! Health remaining: %d\n", game->player_health);
		if (game->player_health <= 0)
		{
			ft_printf("Game Over! The boss has defeated you!\n");
			exit(0);
		}
	}
}

static void	draw_boss_pixel(t_game *game, t_image *frame,
					t_point screen_data, t_pixel_data pixel)
{
	int	tex_x;
	int	tex_y;
	int	color;

	if (pixel.screen_x < 0 || pixel.screen_x >= WIN_WIDTH ||
		pixel.screen_y < 0 || pixel.screen_y >= WIN_HEIGHT)
		return ;
	if (screen_data.size <= 0)
		return ;
	tex_x = pixel.sprite_x * frame->width / screen_data.size;
	tex_y = pixel.sprite_y * frame->height / screen_data.size;
	if (tex_x >= frame->width)
		tex_x = frame->width - 1;
	if (tex_y >= frame->height)
		tex_y = frame->height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	color = *(int *)(frame->addr + (tex_y * frame->line_len
				+ tex_x * (frame->bpp / 8)));
	if ((unsigned int)color != 0x000000 && (unsigned int)color != 0xFF000000
		&& screen_data.distance < game->z_buffer[pixel.screen_x])
	{
		*(int *)(game->buffer.addr + (pixel.screen_y * game->buffer.line_len
					+ pixel.screen_x * (game->buffer.bpp / 8))) = color;
	}
}

static void	draw_boss_row(t_game *game, t_point screen_data,
					t_pixel_data *pixel, int start_x)
{
	int	start_y;

	start_y = WIN_HEIGHT / 2 - screen_data.size / 2;
	pixel->sprite_x = -1;
	while (++pixel->sprite_x < screen_data.size
		&& start_x + pixel->sprite_x < WIN_WIDTH)
	{
		if (start_x + pixel->sprite_x >= 0)
		{
			pixel->screen_x = start_x + pixel->sprite_x;
			pixel->screen_y = start_y + pixel->sprite_y;
			draw_boss_pixel(game, &game->boss.frames[game->boss.frame],
				screen_data, *pixel);
		}
	}
}

void	draw_boss_sprite(t_game *game, t_point screen_data)
{
	t_pixel_data	pixel;
	int				start_x;
	int				start_y;

	start_x = screen_data.x - screen_data.size / 2;
	start_y = WIN_HEIGHT / 2 - screen_data.size / 2;
	pixel.sprite_y = -1;
	while (++pixel.sprite_y < screen_data.size
		&& start_y + pixel.sprite_y < WIN_HEIGHT)
	{
		if (start_y + pixel.sprite_y >= 0)
			draw_boss_row(game, screen_data, &pixel, start_x);
	}
}
