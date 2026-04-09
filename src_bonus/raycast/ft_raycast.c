/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by username          #+#    #+#             */
/*   Updated: 2026/04/10 00:19:31 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_raycast_check_vertical(t_game *game, t_raycast *ray,
	t_raycast_ctx	*ctx, double aux_distance)
{
	int	wall_or_dor;

	if (ctx->distance.x > ctx->max_size + 1)
	{
		ft_raycast_set_max_size(game, ray, ctx);
		return (1);
	}
	ft_ray_iter_up(ctx->tile_xy, ctx->cuadrant, 1);
	wall_or_dor = ft_is_wall_or_closed_door(game, ctx->tile_xy[0],
			ctx->tile_xy[1]);
	if (wall_or_dor)
	{
		ft_rotate_to_cuadrant(ctx->cuadrant, &aux_distance, &ctx->distance.y);
		ft_calc_ray_position(ray, &ray->origin_position,
			aux_distance, ctx->distance.y);
		if (wall_or_dor == 1)
			ft_ray_type(ray, ctx->cuadrant, 0);
		else
			ft_ray_type_door(ray, ctx->cuadrant, 0);
		if (ray->distance > ctx->max_size)
			ft_raycast_set_max_size(game, ray, ctx);
		return (1);
	}
	return (0);
}

static int	ft_raycast_horizontal_hit(t_game *game, t_raycast *ray,
	t_raycast_ctx	*ctx, double aux_distance)
{
	ctx->distance.y = aux_distance;
	ft_rotate_to_cuadrant(ctx->cuadrant, &ctx->distance.x, &ctx->distance.y);
	ft_calc_ray_position(ray, &(ray->origin_position),
		ctx->distance.x, ctx->distance.y);
	if (ctx->wall_or_dor == 1)
		ft_ray_type(ray, ctx->cuadrant, 1);
	else
		ft_ray_type_door(ray, ctx->cuadrant, 1);
	if (ray->distance > ctx->max_size)
		ft_raycast_set_max_size(game, ray, ctx);
	return (1);
}

static int	ft_raycast_check_horizontal(t_game *game, t_raycast *ray,
	t_raycast_ctx	*ctx, double aux_distance)
{
	if (ctx->distance.y > ctx->max_size + 1)
	{
		ft_raycast_set_max_size(game, ray, ctx);
		return (1);
	}
	ft_ray_iter_right(ctx->tile_xy, ctx->cuadrant, 1);
	ctx->wall_or_dor = ft_is_wall_or_closed_door(game, ctx->tile_xy[0],
			ctx->tile_xy[1]);
	if (ctx->wall_or_dor)
		return (ft_raycast_horizontal_hit(game, ray, ctx, aux_distance));
	return (0);
}

static int	ft_raycast_step(t_game *game, t_raycast *ray, t_raycast_ctx *ctx)
{
	double	aux_distance;

	ft_calc_distance(ctx->cuadrant, ctx->tile_xy, ray->origin_position,
		&ctx->distance);
	aux_distance = ctx->sin_cos[1] * (ctx->distance.y / ctx->sin_cos[0]);
	if (aux_distance < ctx->distance.x)
		return (ft_raycast_check_vertical(game, ray, ctx, aux_distance));
	aux_distance = ctx->sin_cos[0] * (ctx->distance.x / ctx->sin_cos[1]);
	return (ft_raycast_check_horizontal(game, ray, ctx, aux_distance));
}

void	ft_raycast(t_raycast_input *input)
{
	t_raycast_ctx	ctx;

	ctx.angle = input->angle;
	ctx.max_size = input->max_size;
	ctx.origin_position = input->origin_position;
	ctx.cuadrant = 0;
	ft_raycast_init(&ctx.angle, &ctx.cuadrant, ctx.tile_xy,
		input->origin_position);
	ft_bzero(input->ray, sizeof(t_raycast));
	input->ray->origin_position = input->origin_position;
	ctx.sin_cos[0] = ft_sin(ctx.angle);
	ctx.sin_cos[1] = ft_cos(ctx.angle);
	ctx.sin_cos[2] = input->angle;
	while (1)
	{
		if (ft_raycast_step(input->game, input->ray, &ctx))
			break ;
	}
}
