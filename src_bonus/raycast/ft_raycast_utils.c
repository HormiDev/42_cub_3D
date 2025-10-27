/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/10/07 00:00:00 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_ray_iter_up(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[1] += iter;
	else if (cuadrant == 1)
		position_xy[0] -= iter;
	else if (cuadrant == 2)
		position_xy[1] -= iter;
	else
		position_xy[0] += iter;
}

void	ft_ray_iter_right(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[0] += iter;
	else if (cuadrant == 1)
		position_xy[1] += iter;
	else if (cuadrant == 2)
		position_xy[0] -= iter;
	else
		position_xy[1] -= iter;
}

void	ft_calc_distance(int cuadrant, int *tile_ray_xy,
	t_vector2 player_position, t_vector2 *distance)
{
	if (cuadrant == 0)
	{
		distance->x = tile_ray_xy[0] + 1 - player_position.x;
		distance->y = tile_ray_xy[1] + 1 - player_position.y;
	}
	else if (cuadrant == 1)
	{
		distance->x = tile_ray_xy[1] + 1 - player_position.y;
		distance->y = player_position.x - tile_ray_xy[0];
	}
	else if (cuadrant == 2)
	{
		distance->x = player_position.x - tile_ray_xy[0];
		distance->y = player_position.y - tile_ray_xy[1];
	}
	else
	{
		distance->x = player_position.y - tile_ray_xy[1];
		distance->y = tile_ray_xy[0] + 1 - player_position.x;
	}
}

void	ft_rotate_to_cuadrant(int cuadrant, double *distance_x,
	double *distance_y)
{
	double	aux_distance_x;

	aux_distance_x = *distance_x;
	if (cuadrant == 0)
		return ;
	else if (cuadrant == 1)
	{
		*distance_x = -(*distance_y);
		*distance_y = aux_distance_x;
	}
	else if (cuadrant == 2)
	{
		*distance_x = -(*distance_x);
		*distance_y = -(*distance_y);
	}
	else
	{
		*distance_x = *distance_y;
		*distance_y = -aux_distance_x;
	}
}

void	ft_calc_ray_position(t_raycast *ray, t_vector2 *player_position,
	double distance_x, double distance_y)
{
	ray->impact.x = player_position->x + distance_x;
	ray->impact.y = player_position->y + distance_y;
	ray->distance = ft_vector_distance(*player_position, ray->impact);
}
