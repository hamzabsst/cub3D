/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:30:00 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/25 15:43:53 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_texture(t_game *game, t_hit *result, t_ray *data, int side)
{
	if (game->map[data->map_y][data->map_x] == ' ')
		result->txtr = &game->no_texture;
	else if (side == 0)
	{
		if (data->step_x > 0)
			result->txtr = &game->ea_texture;
		else
			result->txtr = &game->we_texture;
	}
	else
	{
		if (data->step_y > 0)
			result->txtr = &game->so_texture;
		else
			result->txtr = &game->no_texture;
	}
}

static int	perform_dda(t_game *game, t_ray *data)
{
	int	side;
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->side_x < data->side_y)
		{
			data->side_x += data->delta_x;
			data->map_x += data->step_x;
			side = 0;
		}
		else
		{
			data->side_y += data->delta_y;
			data->map_y += data->step_y;
			side = 1;
		}
		if (game->map[data->map_y][data->map_x] == '1'
			|| game->map[data->map_y][data->map_x] == ' ')
			hit = 1;
	}
	return (side);
}

static void	init_params(t_game *game, double ray_x, double ray_y, t_ray *data)
{
	data->map_x = (int)game->player_x;
	data->map_y = (int)game->player_y;
	data->delta_x = fabs(1 / ray_x);
	data->delta_y = fabs(1 / ray_y);
	if (ray_x < 0)
	{
		data->step_x = -1;
		data->side_x = (game->player_x - data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->side_x = (data->map_x + 1.0 - game->player_x) * data->delta_x;
	}
	if (ray_y < 0)
	{
		data->step_y = -1;
		data->side_y = (game->player_y - data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->side_y = (data->map_y + 1.0 - game->player_y) * data->delta_y;
	}
}

static t_hit	cast_ray(t_game *game, double ray_x, double ray_y)
{
	t_hit	res;
	t_ray	data;
	int		side;

	init_params(game, ray_x, ray_y, &data);
	side = perform_dda(game, &data);
	if (side == 0)
		res.dis = (data.map_x - game->player_x + (1 - data.step_x) / 2) / ray_x;
	else
		res.dis = (data.map_y - game->player_y + (1 - data.step_y) / 2) / ray_y;
	if (res.dis <= 0.001)
		res.dis = 0.001;
	res.is_vert = side;
	set_texture(game, &res, &data, side);
	if (side == 0)
		res.hit_p = game->player_y + res.dis * ray_y;
	else
		res.hit_p = game->player_x + res.dis * ray_x;
	res.hit_p -= floor(res.hit_p);
	return (res);
}

void	raycast(t_game *game)
{
	int		x;
	double	camera_pos;
	double	ray_x;
	double	ray_y;
	t_hit	hit;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_pos = (2.0 * x / WIN_WIDTH) - 1.0;
		ray_x = game->dir_x + game->plane_x * camera_pos;
		ray_y = game->dir_y + game->plane_y * camera_pos;
		hit = cast_ray(game, ray_x, ray_y);
		draw_wall(game, x, hit);
		x++;
	}
}
