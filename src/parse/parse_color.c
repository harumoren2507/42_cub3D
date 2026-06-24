/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 01:00:44 by maono             #+#    #+#             */
/*   Updated: 2026/06/24 01:14:55 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"
#include "parse_internal.h"

static int	is_valid_rgb_commas(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	if (str[0] == ',' || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
		{
			commas++;
			if (str[i + 1] == ',' || str[i + 1] == '\0')
				return (0);
		}
		i++;
	}
	return (commas == 2);
}

static int	parse_rgb(t_game *game, char *str, int *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (!is_valid_rgb_commas(str))
		return (set_error(game, "Color must be R,G,B"));
	parts = ft_split(str, ',');
	if (count_parts(parts) != 3)
		return (free_parts(parts), set_error(game, "Color must be R,G,B"));
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

int	parse_color(t_game *game, char *line, char id, int *flag)
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
