/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 04:04:44 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/19 18:34:32 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	free_map(char **map, int h)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < h)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_parse_temps(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game->tex_paths[i]);
		game->tex_paths[i] = NULL;
		i++;
	}
	i = 0;
	while (i < game->map_row_count)
	{
		free(game->map_rows[i]);
		game->map_rows[i] = NULL;
		i++;
	}
}

static void	free_texture(t_game *game, t_texture *tex)
{
	if (tex->img)
		mlx_destroy_image(game->screen.mlx, tex->img);
	tex->img = NULL;
	tex->addr = NULL;
}

void	free_game(t_game *game)
{
	free_parse_temps(game);
	free_map(game->map, game->map_h);
	game->map = NULL;
	if (!game->screen.mlx)
		return ;
	free_texture(game, &game->textures.north);
	free_texture(game, &game->textures.south);
	free_texture(game, &game->textures.east);
	free_texture(game, &game->textures.west);
	if (game->screen.img)
		mlx_destroy_image(game->screen.mlx, game->screen.img);
	if (game->screen.win)
		mlx_destroy_window(game->screen.mlx, game->screen.win);
	mlx_destroy_display(game->screen.mlx);
	free(game->screen.mlx);
}
