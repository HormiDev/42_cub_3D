/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:14 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/02 16:36:40 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Función de comparación para ordenar jugadores por distancia.
 */
int	ft_compare_by_distance(const void *a, const void *b)
{
	t_player	*player_a;
	t_player	*player_b;

	player_a = (t_player *)a;
	player_b = (t_player *)b;
	if (!player_a->active && !player_b->active)
		return (0);
	if (!player_a->active)
		return (1);
	if (!player_b->active)
		return (-1);
	if (player_a->render_distance > player_b->render_distance)
		return (-1);
	if (player_a->render_distance < player_b->render_distance)
		return (1);
	return (0);
}

/**
 * @brief Crea una copia ordenada del array de jugadores.
 */
void	ft_get_sorted_players(t_game *game)
{
	int	i;
	int j;
	t_player *temp;

	i = 0;
	while(i < MAX_PLAYERS - 1)
	{
		j = 0;
		while(j < MAX_PLAYERS - i - 1)
		{
			if (ft_compare_by_distance(game->ordered_ojects[j], game->ordered_ojects[j + 1]) > 0)
			{
				temp = game->ordered_ojects[j];
				game->ordered_ojects[j] = game->ordered_ojects[j + 1];
				game->ordered_ojects[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Encuentra el índice original de un jugador en el array ordenado.
 */
int	ft_get_original_index(t_game *game, t_player *sorted_player)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (game->players[i].position.x == sorted_player->position.x
			&& game->players[i].position.y == sorted_player->position.y
			&& game->players[i].active == sorted_player->active)
			return (i);
		i++;
	}
	return (-1);
}
