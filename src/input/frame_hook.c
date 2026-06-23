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

#include "cub3D.h"
#include <X11/keysym.h>

static int	is_key_pressed(Display *display, char *keymap, KeySym keysym)
{
	KeyCode	kc;

	kc = XKeysymToKeycode(display, keysym);
	return (keymap[kc / 8] & (1 << (kc % 8)));
}

static void	calc_move_delta(t_game *game, char *keymap, double *mx, double *my)
{
	t_player	*p;
	Display		*dpy;

	p = &game->player;
	dpy = game->screen.display;
	if (is_key_pressed(dpy, keymap, XK_w))
	{
		*mx += cos(p->angle) * MOVE_SPEED;
		*my += sin(p->angle) * MOVE_SPEED;
	}
	if (is_key_pressed(dpy, keymap, XK_s))
	{
		*mx -= cos(p->angle) * MOVE_SPEED;
		*my -= sin(p->angle) * MOVE_SPEED;
	}
	if (is_key_pressed(dpy, keymap, XK_a))
	{
		*mx += sin(p->angle) * MOVE_SPEED;
		*my -= cos(p->angle) * MOVE_SPEED;
	}
	if (is_key_pressed(dpy, keymap, XK_d))
	{
		*mx -= sin(p->angle) * MOVE_SPEED;
		*my += cos(p->angle) * MOVE_SPEED;
	}
}

static void	apply_movement(t_game *game, char *keymap)
{
	t_player	*p;
	double		move_x;
	double		move_y;

	p = &game->player;
	move_x = 0;
	move_y = 0;
	calc_move_delta(game, keymap, &move_x, &move_y);
	if (game->map[(int)p->pos_y][(int)(p->pos_x + move_x)] == CHAR_FLOOR)
		p->pos_x += move_x;
	if (game->map[(int)(p->pos_y + move_y)][(int)p->pos_x] == CHAR_FLOOR)
		p->pos_y += move_y;
}

static void	apply_rotation(t_game *game, char *keymap)
{
	Display	*dpy;

	dpy = game->screen.display;
	if (is_key_pressed(dpy, keymap, XK_Left))
		game->player.angle -= ROTATION_SPEED;
	if (is_key_pressed(dpy, keymap, XK_Right))
		game->player.angle += ROTATION_SPEED;
}

int	frame_hook(void *param)
{
	t_game	*game;
	char	keymap[32];

	game = (t_game *)param;
	XQueryKeymap(game->screen.display, keymap);
	if (is_key_pressed(game->screen.display, keymap, XK_Escape))
		window_close(game);
	apply_movement(game, keymap);
	apply_rotation(game, keymap);
	raycast_frame(game);
	return (0);
}
