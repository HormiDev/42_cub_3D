/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chase_state_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 01:04:11 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_chase_prepare_step(t_player *alien, t_vector2 *target,
	t_vector2 *direction, double *dist)
{
	if (alien->curr_step >= alien->path_len)
		return (0);
	target->x = alien->path[alien->curr_step].x + 0.5;
	target->y = alien->path[alien->curr_step].y + 0.5;
	direction->x = target->x - alien->position.x;
	direction->y = target->y - alien->position.y;
	*dist = ft_vector_distance(alien->position, *target);
	if (*dist < 0.35)
	{
		alien->curr_step++;
		return (0);
	}
	return (1);
}

void	ft_chase_apply_step(t_game *game, t_player *alien,
	t_vector2 *direction)
{
	double	norm;
	double	next_x;
	double	next_y;

	norm = ft_sqrt(direction->x * direction->x + direction->y * direction->y);
	if (norm > 0.001)
	{
		direction->x /= norm;
		direction->y /= norm;
	}
	alien->rotation.x = atan2(direction->y, direction->x) / ft_angle_rad(1.0);
	alien->rotation.x = ft_normalize_angle(alien->rotation.x);
	next_x = alien->position.x + direction->x * alien->speed * game->delta_time;
	next_y = alien->position.y + direction->y * alien->speed * game->delta_time;
	if (!ft_is_blocking_tile(game, (int)next_x, (int)next_y))
	{
		alien->position.x = next_x;
		alien->position.y = next_y;
	}
}

/**
 * @brief Mueve el alien por la ruta BFS hacia el objetivo.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */
void	ft_chase_move_along_path(t_game *game, t_player *alien)
{
	t_vector2	target;
	t_vector2	direction;
	double		dist;

	if (!ft_chase_prepare_step(alien, &target, &direction, &dist))
		return ;
	ft_chase_apply_step(game, alien, &direction);
}

void	ft_chase_set_curr_step(t_player *alien, t_vector_int start)
{
	if (alien->path_len <= 1)
	{
		alien->curr_step = 0;
		return ;
	}
	if (alien->path[0].x == start.x && alien->path[0].y == start.y)
		alien->curr_step = 1;
	else
		alien->curr_step = 0;
	if (alien->curr_step >= alien->path_len)
		alien->curr_step = alien->path_len - 1;
}

/**
 * @brief Recalcula ruta de persecución al tile actual del objetivo.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target jugador objetivo.
 */
void	ft_chase_rebuild_path(t_game *game, t_player *alien, t_player *target)
{
	t_vector_int	start;
	t_vector_int	goal;

	start.x = (int)alien->position.x;
	start.y = (int)alien->position.y;
	goal.x = (int)target->position.x;
	goal.y = (int)target->position.y;
	if (ft_is_blocking_tile(game, goal.x, goal.y))
	{
		alien->path_len = 0;
		alien->curr_step = 0;
		return ;
	}
	ft_bfs_path(game, start, goal, alien->path, &alien->path_len);
	ft_chase_set_curr_step(alien, start);
}