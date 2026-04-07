/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chase_state_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 18:52:58 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Verifica si un tile es bloqueante para el alien.
 *
 * Se considera bloqueante cualquier tile fuera del mapa o marcado como muro
 * en el heatmap (-1), que representa paredes/columnas/puertas cerradas.
 */
int	ft_is_blocking_tile(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width_height[0] || y < 0 || y >= game->width_height[1])
		return (1);
	if (ft_is_wall_or_closed_door(game, x, y))
		return (1);
	return (0);
}

/**
 * @brief Verifica si el player está en FOV 180° y dentro de MAX_RAY_SIZE.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target puntero al jugador.
 * @return 1 si está en rango y FOV, 0 si no.
 */
int	ft_is_player_visible(t_game *game, t_player *alien, t_player *target, double distance)
{
	double		angle_to_target;
	double		angle_diff;
	t_raycast	ray;
	double		pre_angle;

	//printf("Checking player visibility alen angle: %.2f\n", alien->rotation.x);
	pre_angle = alien->rotation.x;
	if (distance > MAX_RAY_SIZE)
		return (0);
	//printf("OriginalDistance: %.2f\n", distance);	
	//printf("atan2 values: %.2f, %.2f\n", target->position.y - alien->position.y, target->position.x - alien->position.x);
	angle_to_target = atan2(target->position.y - alien->position.y,
			target->position.x - alien->position.x) / ft_angle_rad(1.0);
	//printf("Angle to target: %.2f\n", angle_to_target);
	angle_to_target = ft_normalize_angle(angle_to_target);
	//printf("Angle to target: %.2f\n", angle_to_target);
	angle_diff = ft_normalize_relative_angle(angle_to_target - alien->rotation.x);
	//printf("Angle diff: %.2f\n", angle_diff);
	if (angle_diff > -90.0 && angle_diff < 90.0)
	{
		//ft_printf("Player is in fov\n");
		ft_raycast(game, angle_to_target, &ray, distance, alien->position);
		if (ray.type == -1)
		{
			//ft_printf("Player is visible\n");
			alien->rotation.x = angle_to_target;
			return (1);
		}
		//else
			//printf("Player is not visible impact to %f, %f\n", ray.impact.x, ray.impact.y);
	}
	alien->rotation.x = pre_angle;
	return (0);
}
