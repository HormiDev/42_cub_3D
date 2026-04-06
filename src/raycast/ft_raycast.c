/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 22:40:00 by nirmata          #+#    #+#             */
/*   Updated: 2026/04/06 22:40:00 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Calcula el impacto del rayo cuando se alcanza el tamaño máximo.
 * @param game estructura del juego que contiene la información del jugador.
 * @param ray estructura t_raycast donde se almacenará el resultado.
 * @param ctx estructura con ángulo y cuadrante del rayo.
 * @param max_size Tamaño máximo permitido para el rayo.
 */
static void	ft_raycast_max_size(t_game *game, t_raycast *ray,
		t_raycast_ctx *ctx, double max_size)
{
	t_vector2	distance;
	double		sin_cos[2];

	sin_cos[0] = ft_cos(ctx->angle);
	sin_cos[1] = ft_sin(ctx->angle);
	distance.x = sin_cos[0] * max_size;
	distance.y = sin_cos[1] * max_size;
	ft_rotate_to_cuadrant(ctx->cuadrant, &distance.x, &distance.y);
	ray->impact.x = game->player.position.x + distance.x;
	ray->impact.y = game->player.position.y + distance.y;
	ray->distance = max_size;
	ray->type = -1;
}

static int	ft_raycast_check_horizontal(t_game *game, t_raycast *ray,
		t_raycast_ctx *ctx, double max_size)
{
	double	aux_distance;

	if (ctx->distance.x > max_size + 1)
	{
		ft_raycast_max_size(game, ray, ctx, max_size);
		return (1);
	}
	ft_ray_iter_up(ctx->tile_xy, ctx->cuadrant, 1);
	if (game->map[ctx->tile_xy[1]][ctx->tile_xy[0]] == '1')
	{
		aux_distance = ctx->sin_cos[1] * (ctx->distance.y / ctx->sin_cos[0]);
		ft_rotate_to_cuadrant(ctx->cuadrant, &aux_distance, &ctx->distance.y);
		ft_calc_ray_position(ray, &(game->player.position), aux_distance,
			ctx->distance.y);
		ft_ray_type(ray, ctx->cuadrant, 0);
		if (ray->distance > max_size)
			ft_raycast_max_size(game, ray, ctx, max_size);
		return (1);
	}
	return (0);
}

static int	ft_raycast_check_vertical(t_game *game, t_raycast *ray,
		t_raycast_ctx *ctx, double max_size)
{
	double	aux_distance;

	aux_distance = ctx->sin_cos[0] * (ctx->distance.x / ctx->sin_cos[1]);
	if (ctx->distance.y > max_size + 1)
	{
		ft_raycast_max_size(game, ray, ctx, max_size);
		return (1);
	}
	ft_ray_iter_right(ctx->tile_xy, ctx->cuadrant, 1);
	if (game->map[ctx->tile_xy[1]][ctx->tile_xy[0]] == '1')
	{
		ctx->distance.y = aux_distance;
		ft_rotate_to_cuadrant(ctx->cuadrant, &ctx->distance.x,
			&ctx->distance.y);
		ft_calc_ray_position(ray, &(game->player.position), ctx->distance.x,
			ctx->distance.y);
		ft_ray_type(ray, ctx->cuadrant, 1);
		if (ray->distance > max_size)
			ft_raycast_max_size(game, ray, ctx, max_size);
		return (1);
	}
	return (0);
}

static int	ft_raycast_step(t_game *game, t_raycast *ray, t_raycast_ctx *ctx,
		double max_size)
{
	double	aux_distance;

	ft_calc_distance(ctx->cuadrant, ctx->tile_xy, game->player.position,
		&ctx->distance);
	aux_distance = ctx->sin_cos[1] * (ctx->distance.y / ctx->sin_cos[0]);
	if (aux_distance < ctx->distance.x)
		return (ft_raycast_check_horizontal(game, ray, ctx, max_size));
	else
		return (ft_raycast_check_vertical(game, ray, ctx, max_size));
}

/**
 * @brief Realiza un raycasting desde la posición del jugador en un ángulo.
 * @param game estructura del juego que contiene la información del jugador.
 * @param angle Ángulo del rayo en grados.
 * @param ray estructura t_raycast donde se almacenará el resultado.
 * @param max_size Distancia máxima a la que puede llegar el rayo.
 */
void	ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size)
{
	t_raycast_ctx	ctx;

	ctx.cuadrant = 0;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	while (angle >= 90)
	{
		angle -= 90;
		ctx.cuadrant++;
	}
	ctx.angle = angle;
	ft_bzero(ray, sizeof(t_raycast));
	ctx.tile_xy[0] = (int)game->player.position.x;
	ctx.tile_xy[1] = (int)game->player.position.y;
	ctx.sin_cos[0] = ft_sin(angle);
	ctx.sin_cos[1] = ft_cos(angle);
	while (!ft_raycast_step(game, ray, &ctx, max_size))
		;
}
