/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_raycasts.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:15:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/07/24 19:19:53 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

void ft_calculate_raycasts(t_game *game)
{
	int i;
	double fov = 60.0;
	double angle_step = fov / WINDOW_WIDTH;
	double start_angle = game->player.rotation.x - (fov / 2);
	double current_angle;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		current_angle = start_angle + i * angle_step;
		ft_raycast(game, current_angle, &game->raycasts[i], MAX_RAY_SIZE);
		i++;
	}
}