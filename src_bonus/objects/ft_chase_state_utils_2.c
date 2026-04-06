/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chase_state_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 01:04:17 by nirmata          ###   ########.fr       */
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
	if (game->map_heatmap[y][x] == -1)
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
int	ft_is_player_visible(t_player *alien, t_player *target)
{
	double		dist;
	double		angle_to_target;
	double		angle_diff;

	dist = ft_vector_distance(alien->position, target->position);
	if (dist > MAX_RAY_SIZE)
		return (0);
	angle_to_target = atan2(target->position.y - alien->position.y,
			target->position.x - alien->position.x) / ft_angle_rad(1.0);
	angle_to_target = ft_normalize_angle(angle_to_target);
	angle_diff = ft_normalize_relative_angle(angle_to_target - alien->rotation.x);
	if (angle_diff < -90.0 || angle_diff > 90.0)
		return (0);
	return (1);
}