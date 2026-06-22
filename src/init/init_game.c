/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:24:52 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/19 10:31:12 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	open_window(t_game *game)
{
	t_screen	*s;

	s = &game->screen;
	s->mlx = mlx_init();
	if (!s->mlx)
		return (set_error(game, "mlx_init failed"));
	s->win = mlx_new_window(s->mlx, WIN_W, WIN_H, WIN_T);
	if (!s->win)
		return (set_error(game, "mlx_new_window failed"));
	s->img = mlx_new_image(s->mlx, WIN_W, WIN_H);
	if (!s->img)
		return (set_error(game, "mlx_new_image failed"));
	return (0);
}

static int	refresh_screen_addr(t_game *game)
{
	t_screen	*s;

	s = &game->screen;
	s->addr = mlx_get_data_addr(s->img, &s->bpp, &s->line_len, &s->endian);
	if (!s->addr)
		return (set_error(game, "mlx_get_data_addr failed"));
	return (0);
}

int	init_game(t_game *game)
{
	if (open_window(game))
		return (-1);
	if (load_all_textures(game))
		return (-1);
	find_player_pos(game);
	if (refresh_screen_addr(game))
		return (-1);
	return (0);
}
