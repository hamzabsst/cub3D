/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:00:31 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/23 11:43:37 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"
# include <math.h>

# define WIDTH 1024
# define HEIGHT 768
# define SIZE 64

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

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

typedef struct s_player
{
	double		x;
	double		y;
	char		start_dir;
	t_vector	dir;
	t_vector	plane;
}			t_player;

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
}			t_map;

typedef struct s_textures
{
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
}			t_textures;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_image	buffer;
}			t_mlx;

typedef struct s_game
{
	t_map		*map;
	t_player	player;
	t_mlx		mlx;
	t_textures	textures;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
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
