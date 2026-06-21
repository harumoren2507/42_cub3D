/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 22:25:02 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/17 01:53:57 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	set_ray_direction(t_ray *ray, t_player *player, double ray_angle)
{
	ray->ray_angle = ray_angle;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->cell_x = (int)player->pos_x;
	ray->cell_y = (int)player->pos_y;
}

static void	setup_step_axis(double dir, double *delta, double *side,
				int *step, double pos, int cell)
{
	double	offset;

	*delta = fabs(1.0 / dir);
	offset = pos - cell;
	if (dir < 0)
	{
		*step = -1;
		*side = offset * (*delta);
	}
	else
	{
		*step = 1;
		*side = (1.0 - offset) * (*delta);
	}
}

void	ray_setup(t_ray *ray, t_player *player, double ray_angle)
{
	ft_bzero(ray, sizeof(t_ray));
	set_ray_direction(ray, player, ray_angle);
	setup_step_axis(ray->dir_x, &ray->delta_x, &ray->side_x,
		&ray->step_x, player->pos_x, ray->cell_x);
	setup_step_axis(ray->dir_y, &ray->delta_y, &ray->side_y,
		&ray->step_y, player->pos_y, ray->cell_y);
}
