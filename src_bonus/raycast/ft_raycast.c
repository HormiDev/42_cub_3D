/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/07 21:27:39 by ide-dieg         ###   ########.fr       */
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

void	ft_ray_type_door(t_raycast *ray, int cuadrant, int up_right)
{
	if (up_right == 0)
	{
		if (cuadrant == 0)
			ray->type = DOOR_NO;
		else if (cuadrant == 1)
			ray->type = DOOR_WE;
		else if (cuadrant == 2)
			ray->type = DOOR_SO;
		else
			ray->type = DOOR_EA;
	}
	else
	{
		if (cuadrant == 0)
			ray->type = DOOR_EA;
		else if (cuadrant == 1)
			ray->type = DOOR_NO;
		else if (cuadrant == 2)
			ray->type = DOOR_WE;
		else
			ray->type = DOOR_SO;
	}
}

void	ft_raycast_max_size(double angle,
	t_raycast *ray, double max_size, int cuadrant)
{
	t_vector2	distance;
	double		sin_cos[2];

	sin_cos[0] = ft_cos(angle);
	sin_cos[1] = ft_sin(angle);
	distance.x = sin_cos[0] * max_size;
	distance.y = sin_cos[1] * max_size;
	ft_rotate_to_cuadrant(cuadrant, &distance.x, &distance.y);
	ray->impact.x = ray->origin_position.x + distance.x;
	ray->impact.y = ray->origin_position.y + distance.y;
	ray->distance = max_size;
	ray->type = -1;
}

static void	ft_raycast_init(double *angle,
	int *cuadrant, int *tile_ray_xy, t_vector2 origin_position)
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
	tile_ray_xy[0] = origin_position.x;
	tile_ray_xy[1] = origin_position.y;
}

static int	ft_raycast_vertical(t_game *game, int *tile_ray_xy,
	int cuadrant, t_raycast *ray, t_vector2 *distance,
	double *sin_cos, double max_size, double aux_distance)
{
	int	wall_or_dor;

	if (distance->x > max_size + 1)
	{
		ft_raycast_max_size(sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	ft_ray_iter_up(tile_ray_xy, cuadrant, 1);
	wall_or_dor = ft_is_wall_or_closed_door(game, tile_ray_xy[0], tile_ray_xy[1]);
	if (wall_or_dor)
	{
		ft_rotate_to_cuadrant(cuadrant, &aux_distance, &distance->y);
		ft_calc_ray_position(ray, &ray->origin_position,
			aux_distance, distance->y);
		if (wall_or_dor == 1)
			ft_ray_type(ray, cuadrant, 0);
		else
			ft_ray_type_door(ray, cuadrant, 0);
		if (ray->distance > max_size)
			ft_raycast_max_size(sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	return (0);
}

static int	ft_raycast_horizontal(t_game *game, int *tile_ray_xy,
	int cuadrant, t_raycast *ray, t_vector2 *distance,
	double *sin_cos, double max_size, double aux_distance)
{
	int	wall_or_dor;

	if (distance->y > max_size + 1)
	{
		ft_raycast_max_size(sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	ft_ray_iter_right(tile_ray_xy, cuadrant, 1);
	wall_or_dor = ft_is_wall_or_closed_door(game, tile_ray_xy[0], tile_ray_xy[1]);
	if (wall_or_dor)
	{
		distance->y = aux_distance;
		ft_rotate_to_cuadrant(cuadrant, &distance->x, &distance->y);
		ft_calc_ray_position(ray, &(ray->origin_position),
			distance->x, distance->y);
		if (wall_or_dor == 1)
			ft_ray_type(ray, cuadrant, 1);
		else
			ft_ray_type_door(ray, cuadrant, 1);
		if (ray->distance > max_size)
			ft_raycast_max_size(sin_cos[2], ray, max_size, cuadrant);
		return (1);
	}
	return (0);
}

void	ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size, t_vector2 origin_position)
{
	int			tile_ray_xy[2];
	t_vector2	distance;
	double		sin_cos[3];
	int			cuadrant;
	double		aux_distance;

	cuadrant = 0;
	sin_cos[2] = angle;
	ft_raycast_init(&angle, &cuadrant, tile_ray_xy, origin_position);
	ft_bzero(ray, sizeof(t_raycast));
	ray->origin_position = origin_position;
	sin_cos[0] = ft_sin(angle);
	sin_cos[1] = ft_cos(angle);
	while (1)
	{
		ft_calc_distance(cuadrant, tile_ray_xy, ray->origin_position,
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
