/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:04:47 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 10:02:19 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	setup_colors(t_game *game)
{
	game->f_rgb = (game->f_color[0] << 16)
		| (game->f_color[1] << 8) | game->f_color[2];
	game->c_rgb = (game->c_color[0] << 16)
		| (game->c_color[1] << 8) | game->c_color[2];
}

static void	set_direction(t_game *game, double x, double y, double plane_x)
{
	game->dir_x = x;
	game->dir_y = y;
	game->plane_x = plane_x;
	if (plane_x == 0)
		game->plane_y = 0.66;
	else
		game->plane_y = 0;
}

static int	load_texture_image(t_game *game, t_image *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		return (1);
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error("Failed to initialize MiniLibX"));
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D_bonus");
	if (!game->window)
		return (ft_error("Failed to create window"));
	if (load_texture_image(game, &game->no_texture, game->no_path))
		return (ft_error("Failed to load north texture"));
	if (load_texture_image(game, &game->so_texture, game->so_path))
		return (ft_error("Failed to load south texture"));
	if (load_texture_image(game, &game->we_texture, game->we_path))
		return (ft_error("Failed to load west texture"));
	if (load_texture_image(game, &game->ea_texture, game->ea_path))
		return (ft_error("Failed to load east texture"));
	if (load_texture_image(game, &game->door_texture, "./textures/door.xpm"))
		return (ft_error("Failed to load door texture"));
	init_door(game);
	if (game->start_dir == 'N')
		set_direction(game, 0, -1, 0.66);
	else if (game->start_dir == 'S')
		set_direction(game, 0, 1, -0.66);
	else if (game->start_dir == 'E')
		set_direction(game, 1, 0, 0);
	else if (game->start_dir == 'W')
		set_direction(game, -1, 0, 0);
	else
		return (ft_error("Invalid player start direction"));
	return (0);
}

void	init_var(t_game *game)
{
	int	i;

	ft_bzero(game, sizeof(t_game));
	game->player_x = -1.0;
	game->player_y = -1.0;
	game->prev_mouse_x = -1;
	game->mouse_sens = 0.001;
	i = 0;
	while (i < 3)
	{
		game->f_color[i] = -1;
		game->c_color[i] = -1;
		i++;
	}
}
