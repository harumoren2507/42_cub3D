/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_march.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 08:50:19 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/21 08:26:49 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_march_to_wall(t_ray *ray, char **map)
{
	while (map[ray->cell_y][ray->cell_x] != '1')
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->cell_x += ray->step_x;
			ray->side = SIDE_EW;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->cell_y += ray->step_y;
			ray->side = SIDE_NS;
		}
	}
}
