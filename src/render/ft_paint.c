/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:50:37 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

static void	ft_paint_setup_column(t_column_ctx *col, int wall_height,
		t_texture *texture, double ray_distance)
{
	col->texture_iteration = (double)texture->height / (double)wall_height;
	col->mist_density = -(ray_distance / MAX_RAY_SIZE * 100) + 100;
	col->last_texture_pixel = -1;
	if (wall_height > RENDER_HEIGHT)
	{
		col->y = 0;
		col->render_end = RENDER_HEIGHT - 1;
		col->texture_start = (double)((wall_height - RENDER_HEIGHT) / 2.0)
			/ (double)wall_height * (double)texture->height;
	}
	else
	{
		col->y = (RENDER_HEIGHT - wall_height) / 2;
		col->render_end = col->y + wall_height - 1;
		col->texture_start = 0.0;
	}
}

static void	ft_paint_solid_color(t_game *game, int x, t_column_ctx *col,
		t_texture *texture)
{
	ft_mix_color(&game->render->cmx[col->y++][x],
		&texture->texture_color, col->mist_density);
	while (col->y < col->render_end)
	{
		game->render->cmx[col->y][x] = game->render->cmx[col->y
			- 1][x];
		col->y++;
	}
}

static void	ft_paint_textured(t_game *game, int x, t_column_ctx *col,
		t_texture *texture)
{
	while (col->y < col->render_end)
	{
		if (col->last_texture_pixel == (int)col->texture_start)
		{
			game->render->cmx[col->y][x] = game->render->cmx[col->y
				- 1][x];
		}
		else
		{
			ft_mix_color(&game->render->cmx[col->y][x],
				&texture->cmx[(int)col->texture_start][col->texture_x],
				col->mist_density);
			col->last_texture_pixel = (int)col->texture_start;
		}
		col->texture_start += col->texture_iteration;
		col->y++;
	}
}

void	draw_column(t_game *game, int x, t_raycast *ray)
{
	int				wall_height;
	t_texture		*texture;
	t_column_ctx	col;

	if (ray->type < 0 || ray->type > 3 || ray->distance <= 0.0)
		return ;
	wall_height = ft_calculate_wall_height(ray, x);
	if (wall_height <= 0)
		return ;
	texture = get_texture_for_wall(game, ray);
	ft_paint_setup_column(&col, wall_height, texture, ray->distance);
	if (texture->path == NULL)
		ft_paint_solid_color(game, x, &col, texture);
	else
	{
		col.texture_x = ft_calc_texture_x(ray, texture);
		ft_paint_textured(game, x, &col, texture);
	}
}

void	ft_render_3d(t_game *game)
{
	int	i;

	draw_background(game);
	i = 0;
	while (i < RENDER_WIDTH)
	{
		draw_column(game, RENDER_WIDTH - i - 1, &game->raycasts[i]);
		i++;
	}
}
