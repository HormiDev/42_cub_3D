/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_heatmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:46:48 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 16:55:53 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"


static void ft_calc_heat(t_game *game, int index_player)
{
	int	mult;
	int distance;
	t_vector_int pos;

	pos.x = (int)game->players[index_player].position.x;
	pos.y = (int)game->players[index_player].position.y;
	if (game->actions[index_player].walk)
	{
		distance = (int)ft_vector_distance(game->players[index_player].position,
			game->players[5].position);
		if (distance < MAX_RAY_SIZE)
		{
			mult = MAX_RAY_SIZE - distance;
			if (game->actions[index_player].run)
				game->map_heatmap[pos.y][pos.x] += 4 * mult;
			else
				game->map_heatmap[pos.y][pos.x] += 2;
		}
		if (game->actions[index_player].run)
			game->map_heatmap[pos.y][pos.x] += 4;
		else
			game->map_heatmap[pos.y][pos.x] += 2;
	}
	else
		game->map_heatmap[pos.y][pos.x]++;
}

void	ft_update_heatmap(t_game *game)
{
	int	i;

	if (game->current_time - game->heat_time > 1000)
	{
		i = 0;
		game->heat_time = game->current_time;
		while (i < game->config.n_players)
		{
			if (game->players[i].alive)
			{
				ft_calc_heat(game, i);
			}
			i++;
		}
	}
}
