/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 04:25:24 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/14 13:23:12 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	key_to_idx(int key)
{
	if (key == KC_W)
		return (KEY_W);
	if (key == KC_A)
		return (KEY_A);
	if (key == KC_S)
		return (KEY_S);
	if (key == KC_D)
		return (KEY_D);
	if (key == KC_LEFT)
		return (KEY_LEFT);
	if (key == KC_RIGHT)
		return (KEY_RIGHT);
	return (-1);
}

int	key_press(int key, void *param)
{
	t_game	*game;
	int		idx;

	game = (t_game *)param;
	if (key == KC_ESC)
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
	exit(0);
}
