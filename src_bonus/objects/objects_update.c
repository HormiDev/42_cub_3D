/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:25 by username          #+#    #+#             */
/*   Updated: 2026/04/10 01:32:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_get_random_position(t_game *game, int indez, t_vector2 *pos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map_transitable_aux[i][j] == '0'
				&& ft_try_set_random_position(pos, count, indez,
					(t_vector_int){j, i}))
				return (1);
			if (game->map_transitable_aux[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Respawnea el alien en una posición segura dentro del mapa transitable.
 *
 * Intenta encontrar un punto caminable que NO esté dentro del área de exclusión
 * (MAX_RAY_SIZE) de ningún jugador. Si lo consigue, coloca el alien ahí.
 * Si después de un intento no encuentra posición válida, coloca el alien en
 * un punto caminable completamente aleatorio como fallback.
 *
 * @param game estructura del juego con el mapa y jugadores.
 */

void	ft_copy_transitable_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			game->map_transitable_aux[i][j] = game->map_transitable[i][j];
			j++;
		}
		i++;
	}
}

int	ft_find_respawn_candidates(t_game *game)
{
	int	available_count;

	ft_copy_transitable_map(game);
	ft_mark_player_areas(game);
	available_count = ft_aviable_positions(game);
	if (available_count > 0)
		return (available_count);
	ft_copy_transitable_map(game);
	return (ft_aviable_positions(game));
}

void	ft_respawn_alien(t_game *game)
{
	int			avaiable_count;
	int			random_idx;
	long		seed;
	t_vector2	pos;

	if (!game || !game->map_transitable || !game->map_transitable_aux)
		return ;
	pos = game->players[4].position;
	avaiable_count = ft_find_respawn_candidates(game);
	if (avaiable_count <= 0)
		return ;
	seed = game->current_time;
	if (seed <= 0)
		seed = ft_get_time();
	random_idx = (int)(seed % avaiable_count);
	if (!ft_get_random_position(game, random_idx, &pos))
	{
		random_idx = 0;
		ft_get_random_position(game, random_idx, &pos);
	}
	ft_set_alien_pos(game, pos);
}

/**
 * @brief Actualiza las distancias de render de todos los jugadores.
 */
void	ft_update_render_distances(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (game->players[i].active)
			game->players[i].render_distance
				= ft_vector_distance(game->player->position,
					game->players[i].position);
		i++;
	}
}
