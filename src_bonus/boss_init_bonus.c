/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:11:22 by hbousset          #+#    #+#             */
/*   Updated: 2025/09/10 17:34:23 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

static int	has_boss_spawn(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		if (!game->map[i])
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < game->map_width && j < (int)ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == 'X')
			{
				game->boss.x = j + 0.5;
				game->boss.y = i + 0.5;
				game->map[i][j] = '0';
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	init_boss(t_game *game)
{
	if (!has_boss_spawn(game))
	{
		game->boss.active = 0;
		return (0);
	}
	game->boss.speed = 0.01;
	game->boss.frame = 0;
	game->boss.counter = 0;
	game->boss.delay = 8;
	game->boss.active = 1;
	game->hp = 2;
	game->last_dmg_time = 0;
	if (load_boss_frames(game))
		return (1);
	return (0);
}
