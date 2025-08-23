/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:00:31 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 18:12:52 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"
# include <math.h>

# define WIDTH 1024
# define HEIGHT 768

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
	t_image		north_texture;
	t_image		south_texture;
	t_image		west_texture;
	t_image		east_texture;

	// Texture paths
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;

	// Colors
	int			floor_color[3];
	int			ceiling_color[3];
	int			floor_rgb;
	int			ceiling_rgb;
}				t_game;

char	**load_file(char *filename);
int		parse_file(char **lines, t_game *game);
int		process_identifier(char *trimmed, t_game *game);
int		parse_texture(char *line, char **texture_path);
int		validate_wall(t_game *game);
int		parse_map(char **lines, t_game *game);
int		extract_map(char **lines, int start, t_game *game);
int		ft_error(char *msg);
int		load_textures(t_game *game);
void	setup_colors(t_game *game);
int		render_buffer(t_game *game);
int		run_game(t_game *game);
void	cleanup_game(t_game *game);

#endif
