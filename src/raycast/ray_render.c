/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 03:55:59 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/21 04:35:31 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_pixel(t_screen *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->line_len + x * (s->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static int	get_tex_pixel(t_texture *tex, int x, int y)
{
	char	*src;

	src = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)src);
}

void	ray_render_column(t_ray *ray, t_game *game, int col)
{
	int		y;
	int		clip_top;
	double	tex_step;
	double	tex_pos;

	prepare_wall_hit(ray, game);
	y = 0;
	while (y < ray->wall_top)
		put_pixel(&game->screen, col, y++, game->ceil_color);
	clip_top = ray->wall_top - (WIN_H / 2 - ray->wall_height / 2);
	tex_step = (double)ray->texture->height / ray->wall_height;
	tex_pos = clip_top * tex_step;
	y = ray->wall_top;
	while (y < ray->wall_bottom)
	{
		put_pixel(&game->screen, col, y,
			get_tex_pixel(ray->texture, ray->tex_x, (int)tex_pos));
		tex_pos += tex_step;
		y++;
	}
	while (y < WIN_H)
		put_pixel(&game->screen, col, y++, game->floor_color);
}
