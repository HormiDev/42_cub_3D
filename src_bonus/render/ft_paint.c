/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/08 02:36:55 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void draw_column(t_game *game, int x, t_raycast *ray)
{
	int				wall_height;
	int				y;
	double			texture_iteration;
	int				render_end;
	double			texture_start;
	int				texture_x;
	t_texture		*texture;
	int				mist_density;
	int				last_texture_pixel;
	int				height_mid;

	if (ray->type < 0 || ray->type > 7 || ray->distance <= 0.0)
		return (draw_ceiling_and_floor(game, x, game->mist_cloud_height));
	wall_height = ft_calculate_wall_height(ray, x, game);
	if (wall_height <= 0)
		return (draw_ceiling_and_floor(game, x, game->mist_cloud_height));
	texture = get_texture_for_wall(game, ray);
	texture_iteration = (double)texture->height / (double)wall_height;
	if (wall_height > game->config.render_height)
	{
		y = 0;
		render_end = game->config.render_height - 1;
		texture_start = (double)((wall_height - game->config.render_height) / 2.0) / (double)wall_height * (double)texture->height;
	}
	else
	{
		y = (game->config.render_height - wall_height) / 2;
		render_end = y + wall_height;
		texture_start = 0.0;
		draw_ceiling_and_floor(game, x, y);
	}
	mist_density = -(ray->distance / MAX_RAY_SIZE * 100) + 100;
	last_texture_pixel = -1;
	if (texture->path == NULL)
	{
		ft_mix_color(&game->render->cmx[y++][x], &texture->texture_color, mist_density);
		while (y < render_end)
		{
			game->render->cmx[y][x] = game->render->cmx[y - 1][x];
			y++;
		}
	}
	else
	{
		texture_x = ft_calc_texture_x(ray, texture);
		height_mid = game->config.render_height / 2;
		while (y < height_mid)
		{
			if (last_texture_pixel == (int)texture_start)
				game->render->cmx[y][x] = game->render->cmx[y - 1][x];
			else
			{
				ft_mix_color(&game->render->cmx[y][x], &texture->cmx[(int)texture_start][texture_x], mist_density);
				last_texture_pixel = (int)texture_start;
			}
			texture_start += texture_iteration;
			y++;
		}
		texture_start = texture->height / 2.0;
		while (y < render_end)
		{
			if (last_texture_pixel == (int)texture_start)
				game->render->cmx[y][x] = game->render->cmx[y - 1][x];
			else
			{
				ft_mix_color(&game->render->cmx[y][x], &texture->cmx[(int)texture_start][texture_x], mist_density);
				last_texture_pixel = (int)texture_start;
			}
			texture_start += texture_iteration;
			y++;
		}
	}
}

void ft_render_3d(t_game *game)
{
	int			i;

	draw_background(game);
	i = 0;
	while (i < game->config.render_width)
	{
		draw_column(game, game->config.render_width - i - 1, &game->raycasts[i]);
		i++;
	}
}
