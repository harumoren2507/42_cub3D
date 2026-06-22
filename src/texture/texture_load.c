/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:51:39 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/22 22:35:51 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->screen.mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (set_error(game, "Failed to load texture (must be .xpm)"));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (set_error(game, "mlx_get_data_addr failed"));
	return (0);
}

int	load_all_textures(t_game *game)
{
	if (load_texture(game, &game->textures.north, game->tex_paths[TEX_NO]))
		return (-1);
	if (load_texture(game, &game->textures.south, game->tex_paths[TEX_SO]))
		return (-1);
	if (load_texture(game, &game->textures.west, game->tex_paths[TEX_WE]))
		return (-1);
	if (load_texture(game, &game->textures.east, game->tex_paths[TEX_EA]))
		return (-1);
	free(game->tex_paths[TEX_NO]);
	free(game->tex_paths[TEX_SO]);
	free(game->tex_paths[TEX_WE]);
	free(game->tex_paths[TEX_EA]);
	game->tex_paths[TEX_NO] = NULL;
	game->tex_paths[TEX_SO] = NULL;
	game->tex_paths[TEX_WE] = NULL;
	game->tex_paths[TEX_EA] = NULL;
	return (0);
}
