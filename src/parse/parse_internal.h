/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 01:05:39 by maono             #+#    #+#             */
/*   Updated: 2026/06/24 01:42:29 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H

# include "cub3D.h"

int	parse_color(t_game *game, char *line, char id, int *flag);

#endif // !PARSE_INTERNAL_H
