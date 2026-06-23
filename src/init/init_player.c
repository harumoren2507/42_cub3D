/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 19:02:53 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/24 01:27:53 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

static void	set_player_angle(t_player *p, char dir)
{
	if (dir == 'N')
		p->angle = -M_PI / 2;
	else if (dir == 'S')
		p->angle = M_PI / 2;
	else if (dir == 'E')
		p->angle = 0;
	else
		p->angle = M_PI;
}

void	find_player_pos(t_game *game)
{
	int		y;
	int		x;
	char	cell;

	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			cell = game->map[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				game->player.pos_x = x + CELL_CENTER;
				game->player.pos_y = y + CELL_CENTER;
				set_player_angle(&game->player, cell);
				game->map[y][x] = CHAR_FLOOR;
				return ;
			}
			x++;
		}
		y++;
	}
}
