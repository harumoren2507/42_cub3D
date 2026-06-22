/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:08:43 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/23 00:17:21 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define WIN_W   1280
# define WIN_H   720
# define WIN_T   "cub3D"

# define FOV     1.0472

# define SIDE_EW  0
# define SIDE_NS  1

# define TEX_NO   0
# define TEX_SO   1
# define TEX_WE   2
# define TEX_EA   3
# define TEXTURE_COUNT 4

# define KC_W      119
# define KC_A      97
# define KC_S      115
# define KC_D      100
# define KC_LEFT   65361
# define KC_RIGHT  65363
# define KC_ESC    65307

# define KEY_W     0
# define KEY_A     1
# define KEY_S     2
# define KEY_D     3
# define KEY_LEFT  4
# define KEY_RIGHT 5
# define KEY_COUNT 6

# define MOVE_SPEED  0.05
# define ROT_SPEED   0.03

# define EVT_KEYDOWN   2
# define EVT_KEYUP     3
# define EVT_DESTROY   17

# define MAP_MAX_H    1024

# define RGB_MIN       0
# define RGB_MAX       255
# define RED_SHIFT     16
# define GREEN_SHIFT   8

# define MIN_WALL_DIST 0.001
# define CELL_CENTER   0.5

# define CHAR_WALL     '1'
# define CHAR_FLOOR    '0'
# define CHAR_SPACE    ' '

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_textures;

typedef struct s_ray
{
	double		ray_angle;
	double		ray_dist;
	double		dir_x;
	double		dir_y;
	int			cell_x;
	int			cell_y;
	int			step_x;
	int			step_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	int			side;
	double		wall_dist;
	double		wall_frac;
	int			wall_height;
	int			wall_top;
	int			wall_bottom;
	t_texture	*texture;
	int			tex_x;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	angle;
}	t_player;

typedef struct s_screen
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_screen;

typedef struct s_game
{
	t_screen	screen;
	t_player	player;
	t_textures	textures;
	char		**map;
	int			map_h;
	int			map_w;
	int			ceil_color;
	int			floor_color;
	int			keys[KEY_COUNT];
	char		*tex_paths[TEXTURE_COUNT];
	int			tex_loaded[TEXTURE_COUNT];
	int			floor_loaded;
	int			ceil_loaded;
	char		*map_rows[MAP_MAX_H];
	int			map_row_count;
	char		*error_msg;
}	t_game;

#endif
