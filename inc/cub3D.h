/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:00:31 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/22 13:56:57 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//dont include random headers nigga, rah kaynin f libft
# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"
# include <math.h>

typedef struct s_player
{
	double	x;
	double	y;
	char	start_dir;
}			t_player;

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
}			t_map;

typedef struct s_game
{
	t_map		*map;
	t_player	player;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color[3];
	int			ceiling_color[3];
}				t_game;

char	**load_file(char *filename);
int		parse_file(char **lines, t_game *game);
int		parse_identifiers(char **lines, t_game *game);
int		parse_map(char **lines, t_game *game);
int		extract_map(char **lines, int start, t_game *game);
int		ft_error(char *msg);
void	init_game(t_game *game);

#endif
