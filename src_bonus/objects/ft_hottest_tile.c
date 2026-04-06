/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hottest_tile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 01:07:21 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_find_hottest_reachable_tile(t_game *game, t_player *alien,
	t_vector_int *pos)
{
	int	best_heat;
	int	y;
	int	x;

	(void)alien;
	best_heat = 0;
	pos->x = -1;
	pos->y = -1;
	y = 0;
	while (y < game->width_height[1])
	{
		x = 0;
		while (x < game->width_height[0])
		{
			if (game->map_heatmap[y][x] > best_heat)
			{
				best_heat = game->map_heatmap[y][x];
				pos->x = x;
				pos->y = y;
			}
			x++;
		}
		y++;
	}
	return (best_heat > 0);
}