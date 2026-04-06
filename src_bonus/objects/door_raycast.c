/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:03 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 23:21:34 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_is_outside_map(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return (1);
	if (x >= game->width_height[0] || y >= game->width_height[1])
		return (1);
	return (0);
}

static void	ft_raycast_door_init(t_game *game, double *angle, int *cuadrant,
		int *tile_ray_xy)
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
	tile_ray_xy[0] = (int)game->player->position.x;
	tile_ray_xy[1] = (int)game->player->position.y;
}

int	ft_raycast_door_hit(t_game *game, double angle, double max_size,
		t_vector_int *door_tile)
{
	int			tile_ray_xy[2];
	t_vector2	distance;
	double		sin_cos[2];
	int			cuadrant;
	double		aux_distance;

	if (!game || !door_tile)
		return (0);
	cuadrant = 0;
	ft_raycast_door_init(game, &angle, &cuadrant, tile_ray_xy);
	sin_cos[0] = ft_sin(angle);
	sin_cos[1] = ft_cos(angle);
	while (1)
	{
		ft_calc_distance(cuadrant, tile_ray_xy, game->player->position,
			&distance);
		aux_distance = sin_cos[1] * (distance.y / sin_cos[0]);
		if (aux_distance < distance.x)
		{
			if (distance.x > max_size + 1)
				return (0);
			ft_ray_iter_up(tile_ray_xy, cuadrant, 1);
		}
		else
		{
			aux_distance = sin_cos[0] * (distance.x / sin_cos[1]);
			if (distance.y > max_size + 1)
				return (0);
			ft_ray_iter_right(tile_ray_xy, cuadrant, 1);
		}
		if (ft_is_outside_map(game, tile_ray_xy[0], tile_ray_xy[1]))
			return (0);
		if (game->map[tile_ray_xy[1]][tile_ray_xy[0]] == '1')
			return (0);
		if (game->map[tile_ray_xy[1]][tile_ray_xy[0]] == 'D')
		{
			door_tile->x = tile_ray_xy[0];
			door_tile->y = tile_ray_xy[1];
			return (1);
		}
	}
	return (0);
}

int	ft_is_wall_or_closed_door(t_game *game, int x, int y)
{
	t_door	*door;

	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
	{
		door = ft_get_door_at(game, x, y);
		if (door && ft_get_door_height(door) > 0.0)
			return (1);
	}
	return (0);
}
