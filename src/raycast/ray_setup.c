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

#include "cub3D.h"

static void	set_ray_direction(t_ray *ray, t_player *player, double ray_angle)
{
	ray->ray_angle = ray_angle;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->cell_x = (int)player->pos_x;
	ray->cell_y = (int)player->pos_y;
}

static void	setup_step_x(t_ray *ray, double pos)
{
	double	offset;

	ray->delta_x = fabs(1.0 / ray->dir_x);
	offset = pos - ray->cell_x;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = offset * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (1.0 - offset) * ray->delta_x;
	}
}

static void	setup_step_y(t_ray *ray, double pos)
{
	double	offset;

	ray->delta_y = fabs(1.0 / ray->dir_y);
	offset = pos - ray->cell_y;
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = offset * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (1.0 - offset) * ray->delta_y;
	}
}

void	ray_setup(t_ray *ray, t_player *player, double ray_angle)
{
	ft_bzero(ray, sizeof(t_ray));
	set_ray_direction(ray, player, ray_angle);
	setup_step_x(ray, player->pos_x);
	setup_step_y(ray, player->pos_y);
}
