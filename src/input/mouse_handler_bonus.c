/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 00:34:13 by maono             #+#    #+#             */
/*   Updated: 2026/06/25 00:39:13 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

int	mouse_move_handler(int x, int y, void *param)
{
	t_game	*game;
	int		center_x;
	int		delta;

	game = (t_game *)param;
	(void)y;
	if (game->state == STATE_PAUSED)
		return (0);
	center_x = WINDOW_WIDTH / 2;
	delta = x - center_x;
	if (delta == 0)
		return (0);
	game->player.angle += delta * ROTATION_SPEED;
	mlx_mouse_move(game->screen.mlx, game->screen.win, center_x, WINDOW_HEIGHT
		/ 2);
	return (0);
}

int	mouse_enter_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->state = STATE_PLAYING;
	return (0);
}

int	mouse_leave_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->state = STATE_PAUSED;
	return (0);
}
