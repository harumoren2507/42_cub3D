/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:53:04 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/20 01:00:50 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	raycast_frame(t_game *game)
{
	t_ray	ray;
	double	dist_to_plane;
	double	ray_angle;
	int		col;

	dist_to_plane = (WIN_W / 2.0) / tan(FOV / 2.0);
	col = 0;
	while (col < WIN_W)
	{
		ray_angle = game->player.angle
			+ atan((col + 0.5 - WIN_W / 2.0) / dist_to_plane);
		ray_setup(&ray, &game->player, ray_angle);
		ray_march_to_wall(&ray, game->map);
		ray_render_column(&ray, game, col);
		col++;
	}
	mlx_put_image_to_window(game->screen.mlx, game->screen.win,
		game->screen.img, 0, 0);
	return (1);
}
