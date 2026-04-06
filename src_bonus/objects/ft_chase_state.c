/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chase_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 01:09:01 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_chase_try_target(t_player *alien, t_player *candidate,
	t_player **closest, double *closest_dist)
{
	double	dist;

	if (!ft_is_player_visible(alien, candidate))
		return ;
	dist = ft_vector_distance(alien->position, candidate->position);
	if (dist < *closest_dist)
	{
		*closest = candidate;
		*closest_dist = dist;
	}
}

void	ft_chase_scan_players(t_game *game, t_player *alien,
	t_player **closest, double *closest_dist)
{
	int	i;

	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
			ft_chase_try_target(alien, &game->players[i], closest, closest_dist);
		i++;
	}
}


/**
 * @brief Persigue al jugador en modo agresivo usando pathfinding.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target jugador objetivo.
 */
void	ft_chase_player(t_game *game, t_player *alien, t_player *target)
{
	ft_chase_rebuild_path(game, alien, target);
	if (alien->path_len <= 0)
		return ;
	ft_chase_move_along_path(game, alien);
	if (alien->curr_step >= alien->path_len)
	{
		alien->path_len = 0;
		alien->curr_step = 0;
	}
}


/**
 * @brief Busca el player visible más cercano en FOV.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @return puntero al objetivo más cercano o NULL.
 */
t_player	*ft_chase_find_closest_target(t_game *game, t_player *alien)
{
	t_player	*closest;
	double		closest_dist;

	closest = NULL;
	closest_dist = 999.0;
	if (game->player && game->player->alive
		&& game->player->active)
		ft_chase_try_target(alien, game->player, &closest, &closest_dist);
	ft_chase_scan_players(game, alien, &closest, &closest_dist);
	return (closest);
}


/**
 * @brief Actualiza el estado CHASE del alien.
 * @param game estructura del juego.
 * @param alien puntero al alien a actualizar.
 */
void	ft_alien_chase_update(t_game *game, t_player *alien)
{
	t_player	*closest;

	if (!alien || !game)
		return ;
	closest = ft_chase_find_closest_target(game, alien);
	if (!closest)
	{
		alien->state = ALIEN_PATROL;
		alien->path_len = 0;
		alien->curr_step = 0;
		return ;
	}
	ft_chase_player(game, alien, closest);
}
