/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:41:04 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/30 14:20:10 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	find_boss_position(t_game *game)
{
	game->boss.x = game->map_width - 2.5;
	game->boss.y = game->map_height - 2.5;
	while (game->map[(int)game->boss.y][(int)game->boss.x] != '0')
	{
		game->boss.x -= 1.0;
		if (game->boss.x < 1.0)
		{
			game->boss.x = game->map_width - 2.5;
			game->boss.y -= 1.0;
		}
		if (game->boss.y < 1.0)
		{
			game->boss.x = 2.5;
			game->boss.y = 2.5;
			break ;
		}
	}
}

static int	load_boss_frame(t_game *game, int frame_num, char *path)
{
	game->boss.frames[frame_num].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->boss.frames[frame_num].width,
			&game->boss.frames[frame_num].height);
	if (!game->boss.frames[frame_num].img)
		return (ft_error("Failed to load boss frame"));
	game->boss.frames[frame_num].addr = mlx_get_data_addr(
			game->boss.frames[frame_num].img,
			&game->boss.frames[frame_num].bpp,
			&game->boss.frames[frame_num].line_len,
			&game->boss.frames[frame_num].endian);
	if (!game->boss.frames[frame_num].addr)
		return (ft_error("Failed to get boss frame address"));
	return (0);
}

static int	load_boss_frames(t_game *game)
{
	char	*paths[6];
	int		i;

	paths[0] = "./textures/frame_1.xpm";
	paths[1] = "./textures/frame_2.xpm";
	paths[2] = "./textures/frame_3.xpm";
	paths[3] = "./textures/frame_4.xpm";
	paths[4] = "./textures/frame_5.xpm";
	paths[5] = "./textures/frame_6.xpm";
	i = 0;
	while (i < 6)
	{
		if (load_boss_frame(game, i, paths[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_boss(t_game *game)
{
	find_boss_position(game);
	game->boss.speed = 0.02;
	game->boss.frame = 0;
	game->boss.counter = 0;
	game->boss.delay = 8;
	game->boss.active = 1;
	game->boss.last_hit = 0;
	game->player_health = 2;
	game->last_damage_time = 0;
	if (load_boss_frames(game))
		return (1);
	ft_printf("Player health: %d\n", game->player_health);
	return (0);
}
