/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:01 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/02 18:24:30 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Normaliza un ángulo para que esté dentro del rango [0, 360).
 *
 * Esta función toma un ángulo en grados y lo normaliza al rango de 0 a 360 grados,
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

/**
 * @brief Normaliza un ángulo relativo al rango [-180, 180].
 *
 * Esta función toma un ángulo en grados y lo normaliza al rango de -180 a 180 grados,
 * útil para calcular ángulos relativos entre entidades. Ajusta valores mayores a 180
 * o menores o iguales a -180 para que estén dentro del rango.
 *
 * @param angle Ángulo a normalizar en grados.
 * @return El ángulo normalizado en el rango [-180, 180].
 */
double	ft_normalize_relative_angle(double angle)
{
	while (angle > 180)
		angle -= 360;
	while (angle <= -180)
		angle += 360;
	return (angle);
}
