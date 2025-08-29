/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:45:30 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/29 11:46:35 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	cleanup_textures(t_game *game)
{
	if (game->no_texture.img)
		mlx_destroy_image(game->mlx, game->no_texture.img);
	if (game->so_texture.img)
		mlx_destroy_image(game->mlx, game->so_texture.img);
	if (game->we_texture.img)
		mlx_destroy_image(game->mlx, game->we_texture.img);
	if (game->ea_texture.img)
		mlx_destroy_image(game->mlx, game->ea_texture.img);
	if (game->door_texture.img)
		mlx_destroy_image(game->mlx, game->door_texture.img);
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
}

static void	cleanup_paths(t_game *game)
{
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->we_path)
		free(game->we_path);
	if (game->ea_path)
		free(game->ea_path);
}

void	cleanup(t_game *game)
{
	cleanup_textures(game);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		(mlx_destroy_display(game->mlx), free(game->mlx));
	cleanup_paths(game);
	if (game->map)
		ft_free(game->map);
}
