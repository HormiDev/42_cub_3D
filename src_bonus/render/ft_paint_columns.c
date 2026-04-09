/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_columns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:20:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 00:30:08 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static void	ft_set_column_limits(t_game *game, int x, t_column_ctx *ctx)
{
	if (ctx->wall_height > game->config.render_height)
	{
		ctx->y = 0;
		ctx->render_end = game->config.render_height - 1;
		ctx->texture_start
			= (double)((ctx->wall_height - game->config.render_height) / 2.0)
			/ (double) ctx->wall_height *(double) ctx->texture->height;
	}
	else
	{
		ctx->y = (game->config.render_height - ctx->wall_height) / 2;
		ctx->render_end = ctx->y + ctx->wall_height;
		ctx->texture_start = 0.0;
		draw_ceiling_and_floor(game, x, ctx->y);
	}
}

static int	ft_init_column_ctx(t_game *game, int x, t_raycast *ray,
	t_column_ctx	*ctx)
{
	if (ray->type < 0 || ray->type > 7 || ray->distance <= 0.0)
		return (draw_ceiling_and_floor(game, x, game->mist_cloud_height), 0);
	ctx->wall_height = ft_calculate_wall_height(ray, x, game);
	if (ctx->wall_height <= 0)
		return (draw_ceiling_and_floor(game, x, game->mist_cloud_height), 0);
	ctx->texture = get_texture_for_wall(game, ray);
	if (!ctx->texture || ctx->texture->height <= 0 || ctx->texture->width <= 0)
		return (draw_ceiling_and_floor(game, x, game->mist_cloud_height), 0);
	ctx->texture_iteration = (double) ctx->texture->height
		/ (double) ctx->wall_height;
	ft_set_column_limits(game, x, ctx);
	ctx->mist_density = -(ray->distance / MAX_RAY_SIZE * 100) + 100;
	ctx->last_texture_pixel = -1;
	ctx->texture_x = 0;
	ctx->height_mid = game->config.render_height / 2;
	return (1);
}

static void	ft_draw_textured_segment(t_game *game, int x, t_column_ctx *ctx,
				int segment_end)
{
	int	texture_y;

	while (ctx->y < segment_end && ctx->y < ctx->render_end)
	{
		texture_y = ft_clamp_int((int) ctx->texture_start,
				0, ctx->texture->height -1);
		if (ctx->last_texture_pixel == texture_y && ctx->y > 0)
			game->render->cmx[ctx->y][x] = game->render->cmx[ctx->y - 1][x];
		else
		{
			ft_mix_color(&game->render->cmx[ctx->y][x],
				&ctx->texture->cmx[texture_y][ctx->texture_x],
				ctx->mist_density);
			ctx->last_texture_pixel = texture_y;
		}
		ctx->texture_start += ctx->texture_iteration;
		ctx->y++;
	}
}

void	draw_column(t_game *game, int x, t_raycast *ray)
{
	t_column_ctx	ctx;

	if (!ft_init_column_ctx(game, x, ray, &ctx))
		return ;
	if (ctx.texture->path == NULL || ctx.texture->cmx == NULL)
	{
		if (ctx.y < ctx.render_end)
			ft_mix_color(&game->render->cmx[ctx.y++][x],
				&ctx.texture->texture_color, ctx.mist_density);
		while (ctx.y < ctx.render_end)
		{
			game->render->cmx[ctx.y][x] = game->render->cmx[ctx.y - 1][x];
			ctx.y++;
		}
		return ;
	}
	ctx.texture_x = ft_clamp_int(ft_calc_texture_x(ray, ctx.texture), 0,
			ctx.texture->width - 1);
	ft_draw_textured_segment(game, x, &ctx, ctx.height_mid);
	ctx.texture_start = ctx.texture->height / 2.0;
	ft_draw_textured_segment(game, x, &ctx, ctx.render_end);
}
