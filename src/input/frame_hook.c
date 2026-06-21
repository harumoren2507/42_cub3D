/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:31:40 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/18 10:44:58 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	calc_move_delta(t_game *game, double *mx, double *my)
{
	t_player	*p;

	p = &game->player;
	*mx = 0;
	*my = 0;
	if (game->keys[KEY_W])
	{
		*mx += cos(p->angle) * MOVE_SPEED;
		*my += sin(p->angle) * MOVE_SPEED;
	}
	if (game->keys[KEY_S])
	{
		*mx -= cos(p->angle) * MOVE_SPEED;
		*my -= sin(p->angle) * MOVE_SPEED;
	}
	if (game->keys[KEY_A])
	{
		*mx += sin(p->angle) * MOVE_SPEED;
		*my -= cos(p->angle) * MOVE_SPEED;
	}
	if (game->keys[KEY_D])
	{
		*mx -= sin(p->angle) * MOVE_SPEED;
		*my += cos(p->angle) * MOVE_SPEED;
	}
}

static void	apply_movement(t_game *game)
{
	t_player	*p;
	double		move_x;
	double		move_y;

	p = &game->player;
	calc_move_delta(game, &move_x, &move_y);
	if (game->map[(int)p->pos_y][(int)(p->pos_x + move_x)] == CHAR_FLOOR)
		p->pos_x += move_x;
	if (game->map[(int)(p->pos_y + move_y)][(int)p->pos_x] == CHAR_FLOOR)
		p->pos_y += move_y;
}

static void	apply_rotation(t_game *game)
{
	if (game->keys[KEY_LEFT])
		game->player.angle -= ROT_SPEED;
	if (game->keys[KEY_RIGHT])
		game->player.angle += ROT_SPEED;
}

int	frame_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	apply_movement(game);
	apply_rotation(game);
	raycast_frame(game);
	return (0);
}
