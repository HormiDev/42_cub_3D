/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_raycasts.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:15:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/29 18:09:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Calcula los raycasts para cada columna de la ventana.
 *
 * recorre cada columna de la ventana y calcula el raycast correspondiente
 * utilizando la función ft_raycast.
 *
 * @param game contiene la información del jugador y los raycasts.
 */
void	ft_calculate_raycasts(t_game *game)
{
	int		i;
	double	angle_step;
	double	start_angle;
	double	current_angle;

	angle_step = FOV / RENDER_WIDTH;
	start_angle = game->player.rotation.x - (FOV / 2);
	i = 0;
	while (i < RENDER_WIDTH)
	{
		current_angle = start_angle + i * angle_step;
		ft_raycast(game, current_angle, &game->raycasts[i], MAX_RAY_SIZE);
		i++;
	}
}
