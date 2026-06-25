/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 09:15:23 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/25 18:30:06 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_TITLE "cub3D"

# define FOV 1.0472

# define SIDE_EW 0
# define SIDE_NS 1

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEXTURE_COUNT 4

# define KEY_W 0
# define KEY_A 1
# define KEY_S 2
# define KEY_D 3
# define KEY_LEFT 4
# define KEY_RIGHT 5
# define KEY_COUNT 6

# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.03

# define MAP_MAX_HEIGHT 1024

# define RGB_MIN 0
# define RGB_MAX 255
# define RED_SHIFT 16
# define GREEN_SHIFT 8

# define MIN_WALL_DIST 0.001
# define CELL_CENTER 0.5

# define MAP_WALL '1'
# define MAP_FLOOR '0'
# define MAP_VOID ' '

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct s_textures
{
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
}					t_textures;

typedef struct s_ray
{
	double		dist_to_plane;
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
}				t_ray;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			angle;
}					t_player;

typedef struct s_screen
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

}				t_screen;

enum				e_state
{
	STATE_PAUSED,
	STATE_PLAYING
};

typedef struct s_game
{
	t_screen		screen;
	t_player		player;
	t_textures		textures;
	char			**map;
	int				map_h;
	int				map_w;
	int				ceil_color;
	int				floor_color;
	int				keys[KEY_COUNT];
	char			*tex_paths[TEXTURE_COUNT];
	int				tex_loaded[TEXTURE_COUNT];
	int				floor_loaded;
	int				ceil_loaded;
	char			*map_rows[MAP_MAX_HEIGHT];
	int				map_row_count;
	char			*error_msg;
	enum e_state	state;
}					t_game;

int					is_whitespace(char c);
int					parse_cub_file(t_game *game, char *path);
int					parse_header_line(t_game *game, char *line);
int					map_add_row(t_game *game, char *line);
int					build_map(t_game *game);
int					validate_map_chars(t_game *game);
int					validate_parsed(t_game *game);
int					validate_map_closed(t_game *game);
void				free_parts(char **parts);
int					count_parts(char **parts);
int					is_num_str(char *str);

/* Game Initialization & Textures */
int					init_game(t_game *game);
void				find_player_pos(t_game *game);
int					load_texture(t_game *game, t_texture *tex, char *path);
int					load_all_textures(t_game *game);

/* User Input & Event Hooks */
int					key_press(int key, void *param);
int					key_release(int key, void *param);
int					window_close(void *param);
int					frame_hook(void *param);

/* Raycasting Engine */
void				ray_setup(t_ray *ray, t_player *player, double ray_angle);
void				ray_march_to_wall(t_ray *ray, char **map);
void				prepare_wall_hit(t_ray *ray, t_game *game);
void				ray_render_column(t_ray *ray, t_game *game, int col);
int					raycast_frame(t_game *game);

/* Memory Cleanup */
void				free_map(char **map, int h);
void				free_game(t_game *game);
int					set_error(t_game *game, char *msg);

#endif
