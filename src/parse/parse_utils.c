/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:32:17 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/22 22:46:14 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	count_parts(char **parts)
{
	int	i;

	if (!parts)
		return (0);
	i = 0;
	while (parts[i])
		i++;
	return (i);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
