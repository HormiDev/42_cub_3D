/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patrol_state_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:46:48 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 01:38:13 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_patrol_prepare_step(t_player *alien, t_vector2 *target,
		t_vector2 *direction, double *dist)
{
	if (alien->curr_step >= alien->path_len)
		return (0);
	target->x = alien->path[alien->curr_step].x + 0.5;
	target->y = alien->path[alien->curr_step].y + 0.5;
	direction->x = target->x - alien->position.x;
	direction->y = target->y - alien->position.y;
	*dist = ft_vector_distance(alien->position, *target);
	if (*dist < 0.4)
	{
		alien->curr_step++;
		return (0);
	}
	return (1);
}

void	ft_patrol_apply_step(t_game *game, t_player *alien,
		t_vector2 *direction)
{
	double	norm;

	norm = ft_sqrt(direction->x * direction->x + direction->y * direction->y);
	if (norm > 0.001)
	{
		direction->x /= norm;
		direction->y /= norm;
	}
	alien->rotation.x = atan2(direction->y, direction->x) / ft_angle_rad(1.0);
	alien->rotation.x = ft_normalize_angle(alien->rotation.x);
	alien->position.x += direction->x * alien->speed * game->delta_time;
	alien->position.y += direction->y * alien->speed * game->delta_time;
}

void	ft_move_along_path(t_game *game, t_player *alien)
{
	t_vector2	target;
	t_vector2	direction;
	double		dist;

	if (!ft_patrol_prepare_step(alien, &target, &direction, &dist))
		return ;
	ft_patrol_apply_step(game, alien, &direction);
}

void	ft_patrol_update_retry_timer(double *retry_timer,
		t_vector_int *last_goal, t_player *alien)
{
	*retry_timer += 0.016;
	if (*retry_timer >= 2.0 || alien->path_len == 0)
	{
		*retry_timer = 0.0;
		last_goal->x = -1;
		last_goal->y = -1;
		alien->path_len = 0;
		alien->curr_step = 0;
	}
}

void	ft_patrol_search_path(t_game *game, t_player *alien, t_vector_int goal,
		t_vector_int *last_goal)
{
	t_vector_int	start;
	t_bfs_request	request;
	t_bfs_result	result;

	if (goal.x == last_goal->x && goal.y == last_goal->y)
		return ;
	*last_goal = goal;
	start.x = (int)alien->position.x;
	start.y = (int)alien->position.y;
	request.start = start;
	request.goal = goal;
	result.path = alien->path;
	result.path_len = &alien->path_len;
	ft_bfs_path(game, request, result);
}
