/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:03 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/12 21:19:22 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_is_wall_or_closed_door(t_game *game, int x, int y)
{
	if (game->map[y][x] == '0')
		return (0);
	else if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		return (1);
	else if (game->map[y][x] == 'D')
		return (2);
	return (0);
}
