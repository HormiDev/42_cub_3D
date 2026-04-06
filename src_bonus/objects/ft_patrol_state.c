/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patrol_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:46:48 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/07 01:06:36 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_patrol_set_goal_from_player(t_player *alien, t_player *player,
	t_vector_int *goal)
{
	double	dist;

	if (!player || !player->active || !player->alive)
		return (0);
	dist = ft_vector_distance(alien->position, player->position);
	if (dist >= 4.0 || dist <= 0.1)
		return (0);
	goal->x = (int)player->position.x;
	goal->y = (int)player->position.y;
	return (1);
}

int	ft_patrol_find_near_player_goal(t_game *game, t_player *alien,
	t_vector_int *goal)
{
	int	i;

	if (game->player && game->player->alive)
	{
		if (ft_patrol_set_goal_from_player(alien, game->player, goal))
			return (1);
	}
	i = 0;
	while (i < game->config.n_players)
	{
		if (ft_patrol_set_goal_from_player(alien, &game->players[i], goal))
			return (1);
		i++;
	}
	return (0);
}

void	ft_patrol_find_and_search_goal(t_game *game, t_player *alien,
	t_vector_int *last_goal)
{
	t_vector_int	goal;

	if (alien->path_len != 0)
		return ;
	if (ft_patrol_find_near_player_goal(game, alien, &goal))
	{
		ft_patrol_search_path(game, alien, goal, last_goal);
		return ;
	}
	if (!ft_find_hottest_reachable_tile(game, alien, &goal))
		return ;
	ft_patrol_search_path(game, alien, goal, last_goal);
}

void	ft_patrol_move_and_cleanup(t_game *game, t_player *alien,
	t_vector_int *last_goal)
{
	if (alien->path_len == 0)
		return ;
	ft_move_along_path(game, alien);
	if (alien->curr_step >= alien->path_len)
	{
		alien->path_len = 0;
		alien->curr_step = 0;
		last_goal->x = -1;
		last_goal->y = -1;
	}
}

void	ft_alien_patrol_update(t_game *game, t_player *alien)
{
	static t_vector_int	last_goal = {-1, -1};
	static double		retry_timer = 0.0;

	if (!alien || !game)
		return ;
	ft_patrol_update_retry_timer(&retry_timer, &last_goal, alien);
	ft_patrol_find_and_search_goal(game, alien, &last_goal);
	ft_patrol_move_and_cleanup(game, alien, &last_goal);
}
