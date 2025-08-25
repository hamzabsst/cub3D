/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:00:31 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/25 09:20:38 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"
# include <math.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define ESC 65307
# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65363
# define RIGHT 65361

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_image;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_image		buffer;
	char		**map;
	int			map_width;
	int			map_height;
	double		player_x;
	double		player_y;
	char		start_dir;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_image		no_texture;
	t_image		so_texture;
	t_image		we_texture;
	t_image		ea_texture;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f_color[3];
	int			c_color[3];
	int			f_rgb;
	int			c_rgb;
}				t_game;

typedef struct s_hit
{
	double	dis;
	int		is_vert;
	double	hit_p;
	t_image	*txtr;
}	t_hit;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
}	t_ray;
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
void	manage_player(int keycode, t_game *game);
void	raycast(t_game *game);
void	draw_wall(t_game *game, int screen_x, t_hit hit);
//utils
void	cleanup(t_game *game);
int		ft_error(char *msg);

#endif
