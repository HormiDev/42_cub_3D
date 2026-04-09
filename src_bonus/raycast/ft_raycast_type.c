/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_raycast_type.c                                 :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2025/10/07 00:00:00 by username         #+#    #+#              */
/*   Updated: 2026/04/09 19:28:11 by username        ###   ########.fr        */
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

void ft_raycast_max_size(double angle,
	t_raycast	*ray, double max_size, int cuadrant)
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

void ft_raycast_init(double * angle,
	int	*cuadrant, int *tile_ray_xy, t_vector2 origin_position)
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
