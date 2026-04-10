/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:03 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 01:33:21 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_is_wall_or_closed_door(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
		return (2);
	return (0);
}
