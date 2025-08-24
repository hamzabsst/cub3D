/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:00:31 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/24 08:20:26 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"
# include <math.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_image;

typedef struct s_game
{
	// MLX
	void		*mlx;
	void		*window;
	t_image		buffer;

	// Map
	char		**map;
	int			map_width;
	int			map_height;

	// Player
	double		player_x;
	double		player_y;
	char		start_dir;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	// Textures
	t_image		no_texture;
	t_image		so_texture;
	t_image		we_texture;
	t_image		ea_texture;

	// Texture paths
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

	// Colors
	int			f_color[3];
	int			c_color[3];
	int			f_rgb;
	int			c_rgb;
}				t_game;

//parsing
char	**load_file(char *filename);
void	init_variables(t_game *game);
int		parse_file(char **lines, t_game *game);
int		process_identifier(char *trimmed, t_game *game);
int		parse_texture(char *line, char **texture_path);
int		validate_wall(t_game *game);
int		parse_map(char **lines, t_game *game);
int		extract_map(char **lines, int start, t_game *game);
int		init_game(t_game *game);

//game
int		run_game(t_game *game);

//utils
void	cleanup(t_game *game);
int		ft_error(char *msg);

#endif
