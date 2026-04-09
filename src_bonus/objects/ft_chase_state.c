/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chase_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 00:19:55 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target jugador objetivo.
 */
void	ft_chase_player(t_game *game, t_player *alien)
{
	t_raycast	ray;

	ft_raycast(&(t_raycast_input){game, alien->rotation.x, &ray,
		alien->speed * game->delta_time, alien->position});
	if (ray.type == -1)
	{
		alien->position.x = ray.impact.x;
		alien->position.y = ray.impact.y;
	}
}