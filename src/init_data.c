/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:04:47 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/24 08:21:21 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (1);
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error("Failed to initialize MiniLibX"));
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
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

static void	init_texture(t_game *game)
{
	int	i;

	game->no_texture.img = NULL;
	game->no_texture.addr = NULL;
	game->so_texture.img = NULL;
	game->so_texture.addr = NULL;
	game->we_texture.img = NULL;
	game->we_texture.addr = NULL;
	game->ea_texture.img = NULL;
	game->ea_texture.addr = NULL;
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
	i = 0;
	while (i < 3)
	{
		game->f_color[i] = -1;
		game->c_color[i] = -1;
		i++;
	}
	game->f_rgb = 0;
	game->c_rgb = 0;
}

void	init_variables(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = -1.0;
	game->player_y = -1.0;
	game->start_dir = '\0';
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = 0.0;
	game->mlx = NULL;
	game->window = NULL;
	game->buffer.img = NULL;
	game->buffer.addr = NULL;
	game->buffer.bits_per_pixel = 0;
	game->buffer.line_length = 0;
	game->buffer.endian = 0;
	game->buffer.width = 0;
	game->buffer.height = 0;
	init_texture(game);
}
