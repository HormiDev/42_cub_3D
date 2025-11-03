/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin_cos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:02:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/03 19:37:39 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Convierte grados a radianes.
 *
 * Esta función convierte un ángulo en grados a radianes utilizando la fórmula:
 * radianes = grados * (π / 180).
 * Se utiliza para calcular el seno y coseno de un ángulo en radianes.
 *
 * @param degrees Ángulo en grados.
 * @return El ángulo convertido a radianes.
 */
double ft_angle_rad(double degrees)
{
	return (degrees) * M_PI / 180.0;
}

/**
 * @brief Calcula el seno de un ángulo dado en grados.
 *
 * Esta función utiliza una tabla precalculada de senos para mejorar el rendimiento.
 * Si la tabla no ha sido inicializada, se crea y se llena con los valores del seno
 * para los ángulos de 0 a 89.99 grados (9000 pasos).
 *
 * @param angle Ángulo en grados.
 * @return El seno del ángulo dado.
 */
double ft_sin(double angle)
{
	static double *sin_table;
	int i;
	
	if (sin_table == NULL)
	{
		i = 0;
		sin_table = ft_alloc_lst(sizeof(double) * 9000, 3);
		while (i < 9000)
		{
			sin_table[i] = sin(ft_angle_rad(i / 100.0));
			i++;
		}
	}
	angle = angle * 100;
	if (angle < 0)
		angle += 9000;
	if (angle >= 9000)
		angle -= 9000;
	return sin_table[(int)(angle) % 9000];
}

/**
 * @brief Calcula el coseno de un ángulo dado en grados.
 *
 * Esta función utiliza una tabla precalculada de cosenos para mejorar el rendimiento.
 * Si la tabla no ha sido inicializada, se crea y se llena con los valores del coseno
 * para los ángulos de 0 a 89.99 grados (9000 pasos).
 *
 * @param angle Ángulo en grados.
 * @return El coseno del ángulo dado.
 */
double ft_cos(double angle)
{
	static double *cos_table; 
	int i; 
	if (cos_table == NULL)
	{
		i = 0;

		cos_table = ft_alloc_lst(sizeof(double) * 9000, 3);
		while(i < 9000)
		{
			cos_table[i] = cos(ft_angle_rad(i / 100.0));
			i++;
		}
	}
	angle = angle * 100;
	if (angle < 0)
		angle += 9000;
	if (angle >= 9000)
		angle -= 9000;
	return cos_table[(int)(angle) % 9000];
}
/**
	@brief Ajusta el valor del seno según el cuadrante del ángulo.
	@param value Ángulo en grados.
	@return El valor ajustado del seno.
*/
double ft_format_sin(double value)
{
	if (value < 0)
		value += 360.0;
	if (value < 90.0)
		return (ft_sin(value));
	else if (value < 180)
		return (ft_cos(value));
	else if (value < 270.0)
		return (-ft_sin(value));
	else
		return (-ft_cos(value));
}

/**
	@brief Ajusta el valor del coseno según el cuadrante del ángulo.
	@param value Ángulo en grados.
	@return El valor ajustado del coseno.
*/
double ft_format_cos(double value)
{
	if (value < 0)
		value += 360.0;
	if (value < 90.0)
		return (ft_cos(value));
	else if (value < 180)
		return (-ft_sin(value));
	else if (value < 270.0)
		return (-ft_cos(value));
	else
		return (ft_sin(value));
}