/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:53:24 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/24 01:06:34 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse_internal.h"

static int	parse_tex_path(t_game *game, char *line, char *id, int idx)
{
	char	*path;

	if (ft_strncmp(line, id, ft_strlen(id)) != 0)
		return (0);
	if (game->tex_loaded[idx])
		return (set_error(game, "Duplicate texture definition"));
	path = ft_strtrim(line + ft_strlen(id), " \t");
	if (!path || path[0] == '\0')
	{
		free(path);
		return (set_error(game, "Empty texture path"));
	}
	game->tex_paths[idx] = path;
	game->tex_loaded[idx] = 1;
	return (1);
}

static int	parse_textures(t_game *game, char *line)
{
	int	ret;

	ret = parse_tex_path(game, line, "NO ", TEX_NO);
	if (ret != 0)
		return (ret);
	ret = parse_tex_path(game, line, "SO ", TEX_SO);
	if (ret != 0)
		return (ret);
	ret = parse_tex_path(game, line, "WE ", TEX_WE);
	if (ret != 0)
		return (ret);
	return (parse_tex_path(game, line, "EA ", TEX_EA));
}

int	parse_header_line(t_game *game, char *line)
{
	int	ret;

	ret = parse_textures(game, line);
	if (ret == 1)
		return (0);
	if (ret == -1)
		return (-1);
	ret = parse_color(game, line, 'F', &game->floor_loaded);
	if (ret == 1)
		return (0);
	if (ret == -1)
		return (-1);
	ret = parse_color(game, line, 'C', &game->ceil_loaded);
	if (ret == 1)
		return (0);
	if (ret == -1)
		return (-1);
	return (set_error(game, "Unknown header line"));
}
