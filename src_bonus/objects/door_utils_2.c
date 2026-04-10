/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:21:55 by username          #+#    #+#             */
/*   Updated: 2026/04/10 01:35:14 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_get_door_position(t_raycast *ray, t_vector_int *door_pos)
{
	if (ray->type == DOOR_NO)
	{
		(*door_pos).x = (int)ray->impact.x;
		(*door_pos).y = (int)ray->impact.y + 0.5;
	}
	else if (ray->type == DOOR_SO)
	{
		(*door_pos).x = (int)ray->impact.x;
		(*door_pos).y = (int)ray->impact.y - 0.5;
	}
	else if (ray->type == DOOR_WE)
	{
		(*door_pos).x = (int)ray->impact.x - 0.5;
		(*door_pos).y = (int)ray->impact.y;
	}
	else if (ray->type == DOOR_EA)
	{
		(*door_pos).x = (int)ray->impact.x + 0.5;
		(*door_pos).y = (int)ray->impact.y;
	}
}
