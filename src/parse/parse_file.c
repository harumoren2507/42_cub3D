/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 20:01:20 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/21 03:22:55 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	return (line[i] == '\0' || line[i] == '\n');
}

static void	strip_newline(char *line)
{
	int	len;

	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	handle_line(t_game *game, char *line)
{
	if (game->map_row_count > 0)
		return (map_add_row(game, line));
	if (line[0] == MAP_WALL || line[0] == MAP_VOID)
		return (map_add_row(game, line));
	return (parse_header_line(game, line));
}

static int	read_lines(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		if (!is_blank_line(line) || game->map_row_count > 0)
		{
			if (handle_line(game, line))
			{
				free(line);
				return (-1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_cub_file(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (set_error(game, "Cannot open .cub file"));
	if (read_lines(game, fd))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (build_map(game))
		return (-1);
	if (validate_parsed(game))
		return (-1);
	if (validate_map_chars(game))
		return (-1);
	if (validate_map_closed(game))
		return (-1);
	return (0);
}
