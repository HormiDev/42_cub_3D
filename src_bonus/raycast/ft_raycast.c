/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/20 00:50:25 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_ray_type(t_raycast *ray, int cuadrant, int up_right)
{
	if (up_right == 0)
	{
		if (cuadrant == 0)
			ray->type = WALL_NO;
		else if (cuadrant == 1)
			ray->type = WALL_WE;
		else if (cuadrant == 2)
			ray->type = WALL_SO;
		else
			ray->type = WALL_EA;
	}
	else
	{
		if (cuadrant == 0)
			ray->type = WALL_EA;
		else if (cuadrant == 1)
			ray->type = WALL_NO;
		else if (cuadrant == 2)
			ray->type = WALL_WE;
		else
			ray->type = WALL_SO;
	}
}

void	ft_raycast_max_size(t_game *game, double angle,
	t_raycast *ray, double max_size, int cuadrant)
{
	t_vector2	distance;
	double		sin_cos[2];

	sin_cos[0] = ft_cos(angle);
	sin_cos[1] = ft_sin(angle);
	distance.x = sin_cos[0] * max_size;
	distance.y = sin_cos[1] * max_size;
	ft_rotate_to_cuadrant(cuadrant, &distance.x, &distance.y);
	ray->impact.x = game->player.position.x + distance.x;
	ray->impact.y = game->player.position.y + distance.y;
	ray->distance = max_size;
	ray->type = -1;
}

static void	ft_raycast_init(t_game *game, double *angle,
	int *cuadrant, int *tile_ray_xy)
{
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
	while (*angle >= 90)
	{
		*angle -= 90;
		(*cuadrant)++;
	}
	tile_ray_xy[0] = (int)game->player.position.x;
	tile_ray_xy[1] = (int)game->player.position.y;
}

static int	ft_raycast_vertical(t_game *game, int *tile_ray_xy,
	int cuadrant, t_raycast *ray, t_vector2 *distance,
	double *sin_cos, double max_size, double aux_distance)
{
	if (distance->x > max_size + 1)
	{
		ft_raycast_max_size(game, sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	ft_ray_iter_up(tile_ray_xy, cuadrant, 1);
	if (ft_is_wall_or_closed_door(game, tile_ray_xy[0], tile_ray_xy[1]))
	{
		ft_rotate_to_cuadrant(cuadrant, &aux_distance, &distance->y);
		ft_calc_ray_position(ray, &(game->player.position),
			aux_distance, distance->y);
		ft_ray_type(ray, cuadrant, 0);
		if (ray->distance > max_size)
			ft_raycast_max_size(game, sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	return (0);
}

static int	ft_raycast_horizontal(t_game *game, int *tile_ray_xy,
	int cuadrant, t_raycast *ray, t_vector2 *distance,
	double *sin_cos, double max_size, double aux_distance)
{
	if (distance->y > max_size + 1)
	{
		ft_raycast_max_size(game, sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	ft_ray_iter_right(tile_ray_xy, cuadrant, 1);
	if (ft_is_wall_or_closed_door(game, tile_ray_xy[0], tile_ray_xy[1]))
	{
		distance->y = aux_distance;
		ft_rotate_to_cuadrant(cuadrant, &distance->x, &distance->y);
		ft_calc_ray_position(ray, &(game->player.position),
			distance->x, distance->y);
		ft_ray_type(ray, cuadrant, 1);
		if (ray->distance > max_size)
			ft_raycast_max_size(game, sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	return (0);
}

void	ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size)
{
	int			tile_ray_xy[2];
	t_vector2	distance;
	double		sin_cos[3];
	int			cuadrant;
	double		aux_distance;

	cuadrant = 0;
	sin_cos[2] = angle;
	ft_raycast_init(game, &angle, &cuadrant, tile_ray_xy);
	ft_bzero(ray, sizeof(t_raycast));
	sin_cos[0] = ft_sin(angle);
	sin_cos[1] = ft_cos(angle);
	while (1)
	{
		ft_calc_distance(cuadrant, tile_ray_xy, game->player.position,
			&distance);
		aux_distance = sin_cos[1] * (distance.y / sin_cos[0]);
		if (aux_distance < distance.x)
		{
			if (ft_raycast_vertical(game, tile_ray_xy, cuadrant, ray,
					&distance, sin_cos, max_size, aux_distance))
				break ;
		}
		else
		{
			aux_distance = sin_cos[0] * (distance.x / sin_cos[1]);
			if (ft_raycast_horizontal(game, tile_ray_xy, cuadrant, ray,
					&distance, sin_cos, max_size, aux_distance))
				break ;
		}
	}
}
