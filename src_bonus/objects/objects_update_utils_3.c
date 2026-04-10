/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 01:30:46 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 01:32:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_set_alien_pos(t_game *game, t_vector2 pos)
{
	t_player	*alien;

	alien = &game->players[4];
	alien->position.x = pos.x;
	alien->position.y = pos.y;
	alien->active = 1;
	alien->state = ALIEN_IDLE;
}
