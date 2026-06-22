/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:13:05 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/15 04:10:19 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	validate_parsed(t_game *game)
{
	if (!game->tex_loaded[TEX_NO] || !game->tex_loaded[TEX_SO]
		|| !game->tex_loaded[TEX_WE] || !game->tex_loaded[TEX_EA])
		return (set_error(game, "Missing texture definition (NO/SO/WE/EA)"));
	if (!game->floor_loaded)
		return (set_error(game, "Missing floor color (F)"));
	if (!game->ceil_loaded)
		return (set_error(game, "Missing ceiling color (C)"));
	if (game->map_h == 0 || game->map_w == 0)
		return (set_error(game, "Map is empty"));
	return (0);
}

static int	is_invalid_border(t_game *game, int y, int x)
{
	if (y == 0 || y == game->map_h - 1
		|| x == 0 || x == game->map_w - 1)
		return (1);
	if (game->map[y - 1][x] == CHAR_SPACE
		|| game->map[y + 1][x] == CHAR_SPACE
		|| game->map[y][x - 1] == CHAR_SPACE
		|| game->map[y][x + 1] == CHAR_SPACE)
		return (1);
	return (0);
}

void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

int	is_num_str(char *str)
{
	int	i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			while (is_whitespace(str[i]))
				i++;
			if (str[i] == '\0')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_map_closed(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < game->map_h)
	{
		x = -1;
		while (++x < game->map_w)
		{
			c = game->map[y][x];
			if (c == CHAR_FLOOR || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (is_invalid_border(game, y, x))
					return (set_error(game, "Map is not closed"));
			}
		}
	}
	return (0);
}
