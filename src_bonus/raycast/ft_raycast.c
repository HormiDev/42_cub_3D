/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_raycast.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2025/10/07 00:00:00 by username         #+#    #+#              */
/*   Updated: 2026/04/09 19:55:52 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int ft_raycast_check_vertical(t_game * game, t_raycast * ray,
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

static int ft_raycast_horizontal_hit(t_game * game, t_raycast * ray,
	t_raycast_ctx	*ctx, double aux_distance, int wall_or_dor)
{
	ctx->distance.y = aux_distance;
	ft_rotate_to_cuadrant(ctx->cuadrant, &ctx->distance.x, &ctx->distance.y);
	ft_calc_ray_position(ray, &(ray->origin_position),
		ctx->distance.x, ctx->distance.y);
	if (wall_or_dor == 1)
		ft_ray_type(ray, ctx->cuadrant, 1);
	else
		ft_ray_type_door(ray, ctx->cuadrant, 1);
	if (ray->distance > ctx->max_size)
		ft_raycast_set_max_size(game, ray, ctx);
	return (1);
}

static int ft_raycast_check_horizontal(t_game * game, t_raycast * ray,
	t_raycast_ctx	*ctx, double aux_distance)
{
	int	wall_or_dor;

	if (ctx->distance.y > ctx->max_size + 1)
	{
		ft_raycast_set_max_size(game, ray, ctx);
		return (1);
	}
	ft_ray_iter_right(ctx->tile_xy, ctx->cuadrant, 1);
	wall_or_dor = ft_is_wall_or_closed_door(game, ctx->tile_xy[0],
		ctx->tile_xy[1]);
	if (wall_or_dor)
		return ((ft_raycast_horizontal_hit(game, ray, ctx, aux_distance, wall_or_dor)));
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

void ft_raycast(t_game * game, double angle, t_raycast * ray,
	double	max_size, t_vector2 origin_position)
{
	t_raycast_ctx	ctx;

	ctx.angle = angle;
	ctx.max_size = max_size;
	ctx.origin_position = origin_position;
	ctx.cuadrant = 0;
	ft_raycast_init(&ctx.angle, &ctx.cuadrant, ctx.tile_xy, origin_position);
	ft_bzero(ray, sizeof(t_raycast));
	ray->origin_position = origin_position;
	ctx.sin_cos[0] = ft_sin(ctx.angle);
	ctx.sin_cos[1] = ft_cos(ctx.angle);
	ctx.sin_cos[2] = angle;
	while (1)
	{
		if (ft_raycast_step(game, ray, &ctx))
			break ;
	}
}
