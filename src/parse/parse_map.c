/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 15:26:10 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/20 16:29:35 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_add_row(t_game *game, char *line)
{
	if (game->map_row_count >= MAP_MAX_H)
		return (set_error(game, "Map exceeds maximum height"));
	game->map_rows[game->map_row_count] = ft_strdup(line);
	if (!game->map_rows[game->map_row_count])
		return (set_error(game, "Memory allocation failed"));
	game->map_row_count++;
	return (0);
}

static int	max_row_width(t_game *game)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < game->map_row_count)
	{
		len = (int)ft_strlen(game->map_rows[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_row(char *raw, int width)
{
	char	*padded;
	int		len;
	int		i;

	padded = ft_calloc(width + 1, 1);
	if (!padded)
		return (NULL);
	len = (int)ft_strlen(raw);
	ft_memcpy(padded, raw, len);
	i = len;
	while (i < width)
	{
		padded[i] = CHAR_SPACE;
		i++;
	}
	return (padded);
}

int	validate_map_chars(t_game *game)
{
	int		y;
	int		x;
	int		players;
	char	c;

	players = 0;
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				players++;
			else if (c != CHAR_FLOOR && c != CHAR_WALL && c != CHAR_SPACE)
				return (set_error(game, "Invalid character in map"));
			x++;
		}
		y++;
	}
	if (players != 1)
		return (set_error(game, "Player count must be exactly 1"));
	return (0);
}

int	build_map(t_game *game)
{
	int	i;

	game->map_w = max_row_width(game);
	game->map_h = game->map_row_count;
	if (game->map_h == 0)
		return (set_error(game, "Map is empty"));
	game->map = ft_calloc(game->map_h + 1, sizeof(char *));
	if (!game->map)
		return (set_error(game, "Memory allocation failed"));
	i = 0;
	while (i < game->map_h)
	{
		game->map[i] = pad_row(game->map_rows[i], game->map_w);
		if (!game->map[i])
			return (set_error(game, "Memory allocation failed"));
		free(game->map_rows[i]);
		game->map_rows[i] = NULL;
		i++;
	}
	game->map_row_count = 0;
	return (0);
}
