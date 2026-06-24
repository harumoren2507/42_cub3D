/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 00:58:37 by maono             #+#    #+#             */
/*   Updated: 2026/06/25 00:58:38 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/keysym.h>

int	key_press_bonus(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == XK_Tab)
		game->state = STATE_PAUSED;
	return (key_press(key, param));
}
