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
#include "libft.h"
#include <stdlib.h>

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

static int	parse_rgb(t_game *game, char *str, int *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = ft_split(str, ',');
	if (count_parts(parts) != 3)
	{
		free_parts(parts);
		return (set_error(game, "Color must be R,G,B"));
	}
	if (!is_num_str(parts[0]) || !is_num_str(parts[1]) || !is_num_str(parts[2]))
	{
		free_parts(parts);
		return (set_error(game, "Color values must be numeric"));
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_parts(parts);
	if (r < RGB_MIN || r > RGB_MAX || g < RGB_MIN || g > RGB_MAX || b < RGB_MIN
		|| b > RGB_MAX)
		return (set_error(game, "Color value out of range (0-255)"));
	*color = (r << RED_SHIFT) | (g << GREEN_SHIFT) | b;
	return (1);
}

static int	parse_color(t_game *game, char *line, char id, int *flag)
{
	char	*rgb_str;
	int		color;

	if (line[0] != id || (line[1] != ' ' && line[1] != '\t'))
		return (0);
	if (*flag)
		return (set_error(game, "Duplicate color definition"));
	rgb_str = ft_strtrim(line + 1, " \t");
	if (!rgb_str || rgb_str[0] == '\0')
	{
		free(rgb_str);
		return (set_error(game, "Missing color values"));
	}
	if (parse_rgb(game, rgb_str, &color) < 0)
	{
		free(rgb_str);
		return (-1);
	}
	free(rgb_str);
	if (id == 'F')
		game->floor_color = color;
	else
		game->ceil_color = color;
	*flag = 1;
	return (1);
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
