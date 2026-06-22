/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:11:07 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/23 00:23:55 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

int		is_whitespace(char c);
int		parse_cub_file(t_game *game, char *path);
int		parse_header_line(t_game *game, char *line);
int		map_add_row(t_game *game, char *line);
int		build_map(t_game *game);
int		validate_map_chars(t_game *game);
int		validate_parsed(t_game *game);
int		validate_map_closed(t_game *game);
void	free_parts(char **parts);
int		count_parts(char **parts);
int		is_num_str(char *str);

int		init_game(t_game *game);
void	find_player_pos(t_game *game);
int		load_texture(t_game *game, t_texture *tex, char *path);
int		load_all_textures(t_game *game);

int		key_press(int key, void *param);
int		key_release(int key, void *param);
int		window_close(void *param);
int		frame_hook(void *param);

void	ray_setup(t_ray *ray, t_player *player, double ray_angle);
void	ray_march_to_wall(t_ray *ray, char **map);
void	prepare_wall_hit(t_ray *ray, t_game *game);
void	ray_render_column(t_ray *ray, t_game *game, int col);
int		raycast_frame(t_game *game);

void	free_map(char **map, int h);
void	free_game(t_game *game);
int		set_error(t_game *game, char *msg);

#endif
