/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/29 17:39:28 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Normaliza un ángulo para que esté dentro del rango [0, 360).
 *
 * Esta función toma un ángulo en grados y lo normaliza,
 * manejando valores negativos y valores mayores o iguales a 360 grados.
 *
 * @param angle Ángulo a normalizar en grados.
 * @return El ángulo normalizado en el rango [0, 360).
 */
double	ft_normalize_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}
