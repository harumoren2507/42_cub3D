/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 04:25:24 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/24 01:32:51 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"
#include <X11/keysym.h>

static int	key_to_idx(int key)
{
	if (key == XK_w)
		return (KEY_W);
	if (key == XK_a)
		return (KEY_A);
	if (key == XK_s)
		return (KEY_S);
	if (key == XK_d)
		return (KEY_D);
	if (key == XK_Left)
		return (KEY_LEFT);
	if (key == XK_Right)
		return (KEY_RIGHT);
	return (-1);
}

int	key_press(int key, void *param)
{
	t_game	*game;
	int		idx;

	game = (t_game *)param;
	if (key == XK_Escape)
		window_close(param);
	idx = key_to_idx(key);
	if (idx >= 0)
		game->keys[idx] = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	t_game	*game;
	int		idx;

	game = (t_game *)param;
	idx = key_to_idx(key);
	if (idx >= 0)
		game->keys[idx] = 0;
	return (0);
}

int	window_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(EXIT_FAILURE);
}
