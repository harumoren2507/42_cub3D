/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maono <maono@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:48 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/25 01:13:32 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

static void	set_wall_dist(t_ray *ray, double player_angle)
{
	if (ray->side == SIDE_EW)
		ray->ray_dist = ray->side_x - ray->delta_x;
	else
		ray->ray_dist = ray->side_y - ray->delta_y;
	ray->wall_dist = ray->ray_dist * cos(ray->ray_angle - player_angle);
	if (ray->wall_dist < MIN_WALL_DIST)
		ray->wall_dist = MIN_WALL_DIST;
}

static void	set_wall_texture(t_ray *ray, t_textures *tex)
{
	if (ray->side == SIDE_EW)
	{
		if (ray->dir_x < 0)
			ray->texture = &tex->east;
		else
			ray->texture = &tex->west;
	}
	else
	{
		if (ray->dir_y < 0)
			ray->texture = &tex->south;
		else
			ray->texture = &tex->north;
	}
}

static void	set_tex_x(t_ray *ray, t_player *player)
{
	if (ray->side == SIDE_EW)
		ray->wall_frac = player->pos_y + ray->ray_dist * ray->dir_y;
	else
		ray->wall_frac = player->pos_x + ray->ray_dist * ray->dir_x;
	ray->wall_frac -= floor(ray->wall_frac);
	ray->tex_x = (int)(ray->wall_frac * ray->texture->width);
	if ((ray->side == SIDE_EW && ray->dir_x > 0) || (ray->side == SIDE_NS
			&& ray->dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

static void	set_wall_bounds(t_ray *ray)
{
	ray->wall_height = (int)(ray->dist_to_plane / ray->wall_dist);
	ray->wall_top = WINDOW_HEIGHT / 2 - ray->wall_height / 2;
	ray->wall_bottom = WINDOW_HEIGHT / 2 + ray->wall_height / 2;
	if (ray->wall_top < 0)
		ray->wall_top = 0;
	if (ray->wall_bottom >= WINDOW_HEIGHT)
		ray->wall_bottom = WINDOW_HEIGHT - 1;
}

void	prepare_wall_hit(t_ray *ray, t_game *game)
{
	set_wall_dist(ray, game->player.angle);
	set_wall_texture(ray, &game->textures);
	set_tex_x(ray, &game->player);
	set_wall_bounds(ray);
}
